#pragma once

#include "opendbc/safety/sunnypilot/safety_mads.h"

#include "opendbc/safety/safety_declarations.h"
#include "opendbc/safety/board/can.h"

// include the safety policies.
#include "opendbc/safety/modes/defaults.h"
#include "opendbc/safety/modes/honda.h"
#include "opendbc/safety/modes/toyota.h"
#include "opendbc/safety/modes/tesla.h"
#include "opendbc/safety/modes/gm.h"
#include "opendbc/safety/modes/ford.h"
#include "opendbc/safety/modes/hyundai.h"
#include "opendbc/safety/modes/chrysler.h"
#include "opendbc/safety/modes/rivian.h"
#include "opendbc/safety/modes/subaru.h"
#include "opendbc/safety/modes/subaru_preglobal.h"
#include "opendbc/safety/modes/mazda.h"
#include "opendbc/safety/modes/nissan.h"
#include "opendbc/safety/modes/volkswagen_mqb.h"
#include "opendbc/safety/modes/volkswagen_pq.h"
#include "opendbc/safety/modes/elm327.h"
#include "opendbc/safety/modes/body.h"

// CAN-FD only safety modes
#ifdef CANFD
#include "opendbc/safety/modes/hyundai_canfd.h"
#endif

uint32_t GET_BYTES(const CANPacket_t *msg, int start, int len) {
  uint32_t ret = 0U;
  for (int i = 0; i < len; i++) {
    const uint32_t shift = i * 8;
    ret |= (((uint32_t)msg->data[start + i]) << shift);
  }
  return ret;
}

const int MAX_WRONG_COUNTERS = 5;

// This can be set by the safety hooks
bool controls_allowed = false;
bool relay_malfunction = false;
bool gas_pressed = false;
bool gas_pressed_prev = false;
bool brake_pressed = false;
bool brake_pressed_prev = false;
bool regen_braking = false;
bool regen_braking_prev = false;
bool steering_disengage;
bool steering_disengage_prev;
bool cruise_engaged_prev = false;
struct sample_t vehicle_speed;
bool vehicle_moving = false;
bool acc_main_on = false;  // referred to as "ACC off" in ISO 15622:2018
int cruise_button_prev = 0;
bool safety_rx_checks_invalid = false;

// for safety modes with torque steering control
int desired_torque_last = 0;       // last desired steer torque
int rt_torque_last = 0;            // last desired torque for real time check
int valid_steer_req_count = 0;     // counter for steer request bit matching non-zero torque
int invalid_steer_req_count = 0;   // counter to allow multiple frames of mismatching torque request bit
struct sample_t torque_meas;       // last 6 motor torques produced by the eps
struct sample_t torque_driver;     // last 6 driver torques measured
uint32_t ts_torque_check_last = 0;
uint32_t ts_steer_req_mismatch_last = 0;  // last timestamp steer req was mismatched with torque

// state for controls_allowed timeout logic
bool heartbeat_engaged = false;             // openpilot enabled, passed in heartbeat USB command
uint32_t heartbeat_engaged_mismatches = 0;  // count of mismatches between heartbeat_engaged and controls_allowed

// for safety modes with angle steering control
uint32_t ts_angle_last = 0;
int desired_angle_last = 0;
struct sample_t angle_meas;         // last 6 steer angles/curvatures


int alternative_experience = 0;

// time since safety mode has been changed
uint32_t safety_mode_cnt = 0U;

uint16_t current_safety_mode = SAFETY_SILENT;
uint16_t current_safety_param = 0;
int current_safety_param_sp = 0;
static const safety_hooks *current_hooks = &nooutput_hooks;
safety_config current_safety_config;

static void generic_rx_checks(void);
static void stock_ecu_check(bool stock_ecu_detected);

bool is_lat_active(void) {
  return controls_allowed || mads_is_lateral_control_allowed_by_mads();
}

static bool is_msg_valid(RxCheck addr_list[], int index) {
  bool valid = true;
  if (index != -1) {
    if (!addr_list[index].status.valid_checksum || !addr_list[index].status.valid_quality_flag || (addr_list[index].status.wrong_counters >= MAX_WRONG_COUNTERS)) {
      valid = false;
      controls_allowed = false;
    }
  }
  return valid;
}

static int get_addr_check_index(const CANPacket_t *to_push, RxCheck addr_list[], const int len) {
  int bus = GET_BUS(to_push);
  int addr = GET_ADDR(to_push);
  int length = GET_LEN(to_push);

  int index = -1;
  for (int i = 0; i < len; i++) {
    // if multiple msgs are allowed, determine which one is present on the bus
    if (!addr_list[i].status.msg_seen) {
      for (uint8_t j = 0U; (j < MAX_ADDR_CHECK_MSGS) && (addr_list[i].msg[j].addr != 0); j++) {
        if ((addr == addr_list[i].msg[j].addr) && (bus == addr_list[i].msg[j].bus) &&
              (length == addr_list[i].msg[j].len)) {
          addr_list[i].status.index = j;
          addr_list[i].status.msg_seen = true;
          break;
        }
      }
    }

    if (addr_list[i].status.msg_seen) {
      int idx = addr_list[i].status.index;
      if ((addr == addr_list[i].msg[idx].addr) && (bus == addr_list[i].msg[idx].bus) &&
          (length == addr_list[i].msg[idx].len)) {
        index = i;
        break;
      }
    }
  }
  return index;
}

static void update_addr_timestamp(RxCheck addr_list[], int index) {
  if (index != -1) {
    uint32_t ts = microsecond_timer_get();
    addr_list[index].status.last_timestamp = ts;
  }
}

static void update_counter(RxCheck addr_list[], int index, uint8_t counter) {
  if (index != -1) {
    uint8_t expected_counter = (addr_list[index].status.last_counter + 1U) % (addr_list[index].msg[addr_list[index].status.index].max_counter + 1U);
    addr_list[index].status.wrong_counters += (expected_counter == counter) ? -1 : 1;
    addr_list[index].status.wrong_counters = CLAMP(addr_list[index].status.wrong_counters, 0, MAX_WRONG_COUNTERS);
    addr_list[index].status.last_counter = counter;
  }
}

static bool rx_msg_safety_check(const CANPacket_t *to_push,
                                const safety_config *cfg,
                                const safety_hooks *safety_hooks) {

  int index = get_addr_check_index(to_push, cfg->rx_checks, cfg->rx_checks_len);
  update_addr_timestamp(cfg->rx_checks, index);

  if (index != -1) {
    // checksum check
    if ((safety_hooks->get_checksum != NULL) && (safety_hooks->compute_checksum != NULL) && !cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].ignore_checksum) {
      uint32_t checksum = safety_hooks->get_checksum(to_push);
      uint32_t checksum_comp = safety_hooks->compute_checksum(to_push);
      cfg->rx_checks[index].status.valid_checksum = checksum_comp == checksum;
    } else {
      cfg->rx_checks[index].status.valid_checksum = cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].ignore_checksum;
    }

    // counter check
    if ((safety_hooks->get_counter != NULL) && (cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].max_counter > 0U)) {
      uint8_t counter = safety_hooks->get_counter(to_push);
      update_counter(cfg->rx_checks, index, counter);
    } else {
      cfg->rx_checks[index].status.wrong_counters = cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].ignore_counter ? 0 : MAX_WRONG_COUNTERS;
    }

    // quality flag check
    if ((safety_hooks->get_quality_flag_valid != NULL) && !cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].ignore_quality_flag) {
      cfg->rx_checks[index].status.valid_quality_flag = safety_hooks->get_quality_flag_valid(to_push);
    } else {
      cfg->rx_checks[index].status.valid_quality_flag = cfg->rx_checks[index].msg[cfg->rx_checks[index].status.index].ignore_quality_flag;
    }
  }
  return is_msg_valid(cfg->rx_checks, index);
}

bool safety_rx_hook(const CANPacket_t *to_push) {
  bool controls_allowed_prev = controls_allowed;

  bool valid = rx_msg_safety_check(to_push, &current_safety_config, current_hooks);
  bool whitelisted = get_addr_check_index(to_push, current_safety_config.rx_checks, current_safety_config.rx_checks_len) != -1;
  if (valid && whitelisted) {
    current_hooks->rx(to_push);
  }

  // Handles gas, brake, and regen paddle
  generic_rx_checks();

  // the relay malfunction hook runs on all incoming rx messages.
  // check all applicable tx msgs for liveness on sending bus.
  // used to detect a relay malfunction or control messages from disabled ECUs like the radar
  const int bus = GET_BUS(to_push);
  const int addr = GET_ADDR(to_push);
  for (int i = 0; i < current_safety_config.tx_msgs_len; i++) {
    const CanMsg *m = &current_safety_config.tx_msgs[i];
    if (m->check_relay) {
      stock_ecu_check((m->addr == addr) && (m->bus == bus));
    }
  }

  // reset mismatches on rising edge of controls_allowed to avoid rare race condition
  if (controls_allowed && !controls_allowed_prev) {
    heartbeat_engaged_mismatches = 0;
  }

  return valid;
}

static bool tx_msg_safety_check(const CANPacket_t *to_send, const CanMsg msg_list[], int len) {
  int addr = GET_ADDR(to_send);
  int bus = GET_BUS(to_send);
  int length = GET_LEN(to_send);

  bool whitelisted = false;
  for (int i = 0; i < len; i++) {
    if ((addr == msg_list[i].addr) && (bus == msg_list[i].bus) && (length == msg_list[i].len)) {
      whitelisted = true;
      break;
    }
  }
  return whitelisted;
}

bool safety_tx_hook(CANPacket_t *to_send) {
  bool whitelisted = tx_msg_safety_check(to_send, current_safety_config.tx_msgs, current_safety_config.tx_msgs_len);
  if ((current_safety_mode == SAFETY_ALLOUTPUT) || (current_safety_mode == SAFETY_ELM327)) {
    whitelisted = true;
  }

  bool safety_allowed = false;
  if (whitelisted) {
    safety_allowed = current_hooks->tx(to_send);
  }

  return !relay_malfunction && whitelisted && safety_allowed;
}

static int get_fwd_bus(int bus_num) {
  int destination_bus;
  if (bus_num == 0) {
    destination_bus = 2;
  } else if (bus_num == 2) {
    destination_bus = 0;
  } else {
    destination_bus = -1;
  }
  return destination_bus;
}

int safety_fwd_hook(int bus_num, int addr) {
  bool blocked = relay_malfunction || current_safety_config.disable_forwarding;

  // Block messages that are being checked for relay malfunctions. Safety modes can opt out of this
  // in the case of selective AEB forwarding
  const int destination_bus = get_fwd_bus(bus_num);
  if (!blocked) {
    for (int i = 0; i < current_safety_config.tx_msgs_len; i++) {
      const CanMsg *m = &current_safety_config.tx_msgs[i];
      if (m->check_relay && !m->disable_static_blocking && (m->addr == addr) && (m->bus == destination_bus)) {
        blocked = true;
        break;
      }
    }
  }

  if (!blocked && (current_hooks->fwd != NULL)) {
    blocked = current_hooks->fwd(bus_num, addr);
  }

  return blocked ? -1 : destination_bus;
}

bool get_longitudinal_allowed(void) {
  return controls_allowed && !gas_pressed_prev;
}

// Given a CRC-8 poly, generate a static lookup table to use with a fast CRC-8
// algorithm. Called at init time for safety modes using CRC-8.
void gen_crc_lookup_table_8(uint8_t poly, uint8_t crc_lut[]) {
  for (uint16_t i = 0U; i <= 0xFFU; i++) {
    uint8_t crc = (uint8_t)i;
    for (int j = 0; j < 8; j++) {
      if ((crc & 0x80U) != 0U) {
        crc = (uint8_t)((crc << 1) ^ poly);
      } else {
        crc <<= 1;
      }
    }
    crc_lut[i] = crc;
  }
}

#ifdef CANFD
void gen_crc_lookup_table_16(uint16_t poly, uint16_t crc_lut[]) {
  for (uint16_t i = 0; i < 256U; i++) {
    uint16_t crc = i << 8U;
    for (uint16_t j = 0; j < 8U; j++) {
      if ((crc & 0x8000U) != 0U) {
        crc = (uint16_t)((crc << 1) ^ poly);
      } else {
        crc <<= 1;
      }
    }
    crc_lut[i] = crc;
  }
}
#endif

// 1Hz safety function called by main. Now just a check for lagging safety messages
void safety_tick(const safety_config *cfg) {
  const uint8_t MAX_MISSED_MSGS = 10U;
  bool rx_checks_invalid = false;
  uint32_t ts = microsecond_timer_get();
  if (cfg != NULL) {
    for (int i=0; i < cfg->rx_checks_len; i++) {
      uint32_t elapsed_time = get_ts_elapsed(ts, cfg->rx_checks[i].status.last_timestamp);
      // lag threshold is max of: 1s and MAX_MISSED_MSGS * expected timestep.
      // Quite conservative to not risk false triggers.
      // 2s of lag is worse case, since the function is called at 1Hz
      uint32_t timestep = 1e6 / cfg->rx_checks[i].msg[cfg->rx_checks[i].status.index].frequency;
      bool lagging = elapsed_time > MAX(timestep * MAX_MISSED_MSGS, 1e6);
      cfg->rx_checks[i].status.lagging = lagging;
      if (lagging) {
        controls_allowed = false;
        mads_exit_controls(MADS_DISENGAGE_REASON_LAG);
      }

      if (lagging || !is_msg_valid(cfg->rx_checks, i)) {
        rx_checks_invalid = true;
      }
    }
  }

  safety_rx_checks_invalid = rx_checks_invalid;
}

static void relay_malfunction_set(void) {
  relay_malfunction = true;
  fault_occurred(FAULT_RELAY_MALFUNCTION);
}

static void generic_rx_checks(void) {
  gas_pressed_prev = gas_pressed;

  // exit controls on rising edge of brake press
  if (brake_pressed && (!brake_pressed_prev || vehicle_moving)) {
    controls_allowed = false;
  }
  brake_pressed_prev = brake_pressed;

  // exit controls on rising edge of regen paddle
  if (regen_braking && (!regen_braking_prev || vehicle_moving)) {
    controls_allowed = false;
  }
  regen_braking_prev = regen_braking;

  // exit controls on rising edge of steering override/disengage
  if (steering_disengage && !steering_disengage_prev) {
    controls_allowed = false;
  }
  steering_disengage_prev = steering_disengage;
}

static void stock_ecu_check(bool stock_ecu_detected) {
  // allow 1s of transition timeout after relay changes state before assessing malfunctioning
  const uint32_t RELAY_TRNS_TIMEOUT = 1U;

  // check if stock ECU is on bus broken by car harness
  if ((safety_mode_cnt > RELAY_TRNS_TIMEOUT) && stock_ecu_detected) {
    relay_malfunction_set();
  }
  mads_state_update(vehicle_moving, acc_main_on, controls_allowed, brake_pressed || regen_braking, steering_disengage);
}

static void relay_malfunction_reset(void) {
  relay_malfunction = false;
  fault_recovered(FAULT_RELAY_MALFUNCTION);
}

// resets values and min/max for sample_t struct
static void reset_sample(struct sample_t *sample) {
  for (int i = 0; i < MAX_SAMPLE_VALS; i++) {
    sample->values[i] = 0;
  }
  update_sample(sample, 0);
}

int set_safety_hooks(uint16_t mode, uint16_t param) {
  const safety_hook_config safety_hook_registry[] = {
    {SAFETY_SILENT, &nooutput_hooks},
    {SAFETY_HONDA_NIDEC, &honda_nidec_hooks},
    {SAFETY_TOYOTA, &toyota_hooks},
    {SAFETY_ELM327, &elm327_hooks},
    {SAFETY_GM, &gm_hooks},
    {SAFETY_HONDA_BOSCH, &honda_bosch_hooks},
    {SAFETY_HYUNDAI, &hyundai_hooks},
    {SAFETY_CHRYSLER, &chrysler_hooks},
    {SAFETY_SUBARU, &subaru_hooks},
    {SAFETY_VOLKSWAGEN_MQB, &volkswagen_mqb_hooks},
    {SAFETY_NISSAN, &nissan_hooks},
    {SAFETY_NOOUTPUT, &nooutput_hooks},
    {SAFETY_HYUNDAI_LEGACY, &hyundai_legacy_hooks},
    {SAFETY_MAZDA, &mazda_hooks},
    {SAFETY_BODY, &body_hooks},
    {SAFETY_FORD, &ford_hooks},
    {SAFETY_RIVIAN, &rivian_hooks},
#ifdef CANFD
    {SAFETY_HYUNDAI_CANFD, &hyundai_canfd_hooks},
#endif
#ifdef ALLOW_DEBUG
    {SAFETY_TESLA, &tesla_hooks},
    {SAFETY_SUBARU_PREGLOBAL, &subaru_preglobal_hooks},
    {SAFETY_VOLKSWAGEN_PQ, &volkswagen_pq_hooks},
    {SAFETY_ALLOUTPUT, &alloutput_hooks},
#endif
  };

  // reset state set by safety mode
  safety_mode_cnt = 0U;
  relay_malfunction = false;
  gas_pressed = false;
  gas_pressed_prev = false;
  brake_pressed = false;
  brake_pressed_prev = false;
  regen_braking = false;
  regen_braking_prev = false;
  steering_disengage = false;
  steering_disengage_prev = false;
  cruise_engaged_prev = false;
  vehicle_moving = false;
  acc_main_on = false;
  cruise_button_prev = 0;
  desired_torque_last = 0;
  rt_torque_last = 0;
  ts_angle_last = 0;
  desired_angle_last = 0;
  ts_torque_check_last = 0;
  ts_steer_req_mismatch_last = 0;
  valid_steer_req_count = 0;
  invalid_steer_req_count = 0;

  // reset samples
  reset_sample(&vehicle_speed);
  reset_sample(&torque_meas);
  reset_sample(&torque_driver);
  reset_sample(&angle_meas);

  controls_allowed = false;
  relay_malfunction_reset();
  safety_rx_checks_invalid = false;

  current_safety_config.rx_checks = NULL;
  current_safety_config.rx_checks_len = 0;
  current_safety_config.tx_msgs = NULL;
  current_safety_config.tx_msgs_len = 0;
  current_safety_config.disable_forwarding = false;

  int set_status = -1;  // not set
  int hook_config_count = sizeof(safety_hook_registry) / sizeof(safety_hook_config);
  for (int i = 0; i < hook_config_count; i++) {
    if (safety_hook_registry[i].id == mode) {
      current_hooks = safety_hook_registry[i].hooks;
      current_safety_mode = mode;
      current_safety_param = param;
      set_status = 0;  // set
    }
  }
  if ((set_status == 0) && (current_hooks->init != NULL)) {
    safety_config cfg = current_hooks->init(param);
    current_safety_config.rx_checks = cfg.rx_checks;
    current_safety_config.rx_checks_len = cfg.rx_checks_len;
    current_safety_config.tx_msgs = cfg.tx_msgs;
    current_safety_config.tx_msgs_len = cfg.tx_msgs_len;
    current_safety_config.disable_forwarding = cfg.disable_forwarding;
    // reset all dynamic fields in addr struct
    for (int j = 0; j < current_safety_config.rx_checks_len; j++) {
      current_safety_config.rx_checks[j].status = (RxStatus){0};
    }
  }
  return set_status;
}

// convert a trimmed integer to signed 32 bit int
int to_signed(int d, int bits) {
  int d_signed = d;
  int max_value = (1 << MAX((bits - 1), 0));
  if (d >= max_value) {
    d_signed = d - (1 << MAX(bits, 0));
  }
  return d_signed;
}

// given a new sample, update the sample_t struct
void update_sample(struct sample_t *sample, int sample_new) {
  for (int i = MAX_SAMPLE_VALS - 1; i > 0; i--) {
    sample->values[i] = sample->values[i-1];
  }
  sample->values[0] = sample_new;

  // get the minimum and maximum measured samples
  sample->min = sample->values[0];
  sample->max = sample->values[0];
  for (int i = 1; i < MAX_SAMPLE_VALS; i++) {
    if (sample->values[i] < sample->min) {
      sample->min = sample->values[i];
    }
    if (sample->values[i] > sample->max) {
      sample->max = sample->values[i];
    }
  }
}

static bool max_limit_check(int val, const int MAX_VAL, const int MIN_VAL) {
  return (val > MAX_VAL) || (val < MIN_VAL);
}

// check that commanded torque value isn't too far from measured
static bool dist_to_meas_check(int val, int val_last, struct sample_t *val_meas,
                        const int MAX_RATE_UP, const int MAX_RATE_DOWN, const int MAX_ERROR) {

  // *** val rate limit check ***
  int highest_allowed_rl = MAX(val_last, 0) + MAX_RATE_UP;
  int lowest_allowed_rl = MIN(val_last, 0) - MAX_RATE_UP;

  // if we've exceeded the meas val, we must start moving toward 0
  int highest_allowed = MIN(highest_allowed_rl, MAX(val_last - MAX_RATE_DOWN, MAX(val_meas->max, 0) + MAX_ERROR));
  int lowest_allowed = MAX(lowest_allowed_rl, MIN(val_last + MAX_RATE_DOWN, MIN(val_meas->min, 0) - MAX_ERROR));

  // check for violation
  return max_limit_check(val, highest_allowed, lowest_allowed);
}

// check that commanded value isn't fighting against driver
static bool driver_limit_check(int val, int val_last, const struct sample_t *val_driver,
                        const int MAX_VAL, const int MAX_RATE_UP, const int MAX_RATE_DOWN,
                        const int MAX_ALLOWANCE, const int DRIVER_FACTOR) {

  // torque delta/rate limits
  int highest_allowed_rl = MAX(val_last, 0) + MAX_RATE_UP;
  int lowest_allowed_rl = MIN(val_last, 0) - MAX_RATE_UP;

  // driver
  int driver_max_limit = MAX_VAL + (MAX_ALLOWANCE + val_driver->max) * DRIVER_FACTOR;
  int driver_min_limit = -MAX_VAL + (-MAX_ALLOWANCE + val_driver->min) * DRIVER_FACTOR;

  // if we've exceeded the applied torque, we must start moving toward 0
  int highest_allowed = MIN(highest_allowed_rl, MAX(val_last - MAX_RATE_DOWN,
                                             MAX(driver_max_limit, 0)));
  int lowest_allowed = MAX(lowest_allowed_rl, MIN(val_last + MAX_RATE_DOWN,
                                           MIN(driver_min_limit, 0)));

  // check for violation
  return max_limit_check(val, highest_allowed, lowest_allowed);
}


// real time check, mainly used for steer torque rate limiter
static bool rt_rate_limit_check(int val, int val_last, const int MAX_RT_DELTA) {

  // *** torque real time rate limit check ***
  int highest_val = MAX(val_last, 0) + MAX_RT_DELTA;
  int lowest_val = MIN(val_last, 0) - MAX_RT_DELTA;

  // check for violation
  return max_limit_check(val, highest_val, lowest_val);
}


// interp function that holds extreme values
static float interpolate(struct lookup_t xy, float x) {

  int size = sizeof(xy.x) / sizeof(xy.x[0]);
  float ret = xy.y[size - 1];  // default output is last point

  // x is lower than the first point in the x array. Return the first point
  if (x <= xy.x[0]) {
    ret = xy.y[0];

  } else {
    // find the index such that (xy.x[i] <= x < xy.x[i+1]) and linearly interp
    for (int i=0; i < (size - 1); i++) {
      if (x < xy.x[i+1]) {
        float x0 = xy.x[i];
        float y0 = xy.y[i];
        float dx = xy.x[i+1] - x0;
        float dy = xy.y[i+1] - y0;
        // dx should not be zero as xy.x is supposed to be monotonic
        dx = MAX(dx, 0.0001);
        ret = (dy * (x - x0) / dx) + y0;
        break;
      }
    }
  }
  return ret;
}

int ROUND(float val) {
  return val + ((val > 0.0) ? 0.5 : -0.5);
}

// Safety checks for longitudinal actuation
bool longitudinal_accel_checks(int desired_accel, const LongitudinalLimits limits) {
  bool accel_valid = get_longitudinal_allowed() && !max_limit_check(desired_accel, limits.max_accel, limits.min_accel);
  bool accel_inactive = desired_accel == limits.inactive_accel;
  return !(accel_valid || accel_inactive);
}

bool longitudinal_speed_checks(int desired_speed, const LongitudinalLimits limits) {
  return !get_longitudinal_allowed() && (desired_speed != limits.inactive_speed);
}

bool longitudinal_transmission_rpm_checks(int desired_transmission_rpm, const LongitudinalLimits limits) {
  bool transmission_rpm_valid = get_longitudinal_allowed() && !max_limit_check(desired_transmission_rpm, limits.max_transmission_rpm, limits.min_transmission_rpm);
  bool transmission_rpm_inactive = desired_transmission_rpm == limits.inactive_transmission_rpm;
  return !(transmission_rpm_valid || transmission_rpm_inactive);
}

bool longitudinal_gas_checks(int desired_gas, const LongitudinalLimits limits) {
  bool gas_valid = get_longitudinal_allowed() && !max_limit_check(desired_gas, limits.max_gas, limits.min_gas);
  bool gas_inactive = desired_gas == limits.inactive_gas;
  return !(gas_valid || gas_inactive);
}

bool longitudinal_brake_checks(int desired_brake, const LongitudinalLimits limits) {
  bool violation = false;
  violation |= !get_longitudinal_allowed() && (desired_brake != 0);
  violation |= desired_brake > limits.max_brake;
  return violation;
}

// Safety checks for torque-based steering commands
bool steer_torque_cmd_checks(int desired_torque, int steer_req, const TorqueSteeringLimits limits) {
  bool violation = false;
  uint32_t ts = microsecond_timer_get();

  if (is_lat_active()) {
    // Some safety models support variable torque limit based on vehicle speed
    int max_torque = limits.max_torque;
    if (limits.dynamic_max_torque) {
      const float fudged_speed = (vehicle_speed.min / VEHICLE_SPEED_FACTOR) - 1.;
      max_torque = interpolate(limits.max_torque_lookup, fudged_speed) + 1;
      max_torque = CLAMP(max_torque, -limits.max_torque, limits.max_torque);
    }

    // *** global torque limit check ***
    violation |= max_limit_check(desired_torque, max_torque, -max_torque);

    // *** torque rate limit check ***
    if (limits.type == TorqueDriverLimited) {
      violation |= driver_limit_check(desired_torque, desired_torque_last, &torque_driver,
                                      max_torque, limits.max_rate_up, limits.max_rate_down,
                                      limits.driver_torque_allowance, limits.driver_torque_multiplier);
    } else {
      violation |= dist_to_meas_check(desired_torque, desired_torque_last, &torque_meas,
                                      limits.max_rate_up, limits.max_rate_down, limits.max_torque_error);
    }
    desired_torque_last = desired_torque;

    // *** torque real time rate limit check ***
    violation |= rt_rate_limit_check(desired_torque, rt_torque_last, limits.max_rt_delta);

    // every RT_INTERVAL set the new limits
    uint32_t ts_elapsed = get_ts_elapsed(ts, ts_torque_check_last);
    if (ts_elapsed > MAX_TORQUE_RT_INTERVAL) {
      rt_torque_last = desired_torque;
      ts_torque_check_last = ts;
    }
  }

  // no torque if controls is not allowed
  if (!is_lat_active() && (desired_torque != 0)) {
    violation = true;
  }

  // certain safety modes set their steer request bit low for one or more frame at a
  // predefined max frequency to avoid steering faults in certain situations
  bool steer_req_mismatch = (steer_req == 0) && (desired_torque != 0);
  if (!limits.has_steer_req_tolerance) {
    if (steer_req_mismatch) {
      violation = true;
    }

  } else {
    if (steer_req_mismatch) {
      if (invalid_steer_req_count == 0) {
        // disallow torque cut if not enough recent matching steer_req messages
        if (valid_steer_req_count < limits.min_valid_request_frames) {
          violation = true;
        }

        // or we've cut torque too recently in time
        uint32_t ts_elapsed = get_ts_elapsed(ts, ts_steer_req_mismatch_last);
        if (ts_elapsed < limits.min_valid_request_rt_interval) {
          violation = true;
        }
      } else {
        // or we're cutting more frames consecutively than allowed
        if (invalid_steer_req_count >= limits.max_invalid_request_frames) {
          violation = true;
        }
      }

      valid_steer_req_count = 0;
      ts_steer_req_mismatch_last = ts;
      invalid_steer_req_count = MIN(invalid_steer_req_count + 1, limits.max_invalid_request_frames);
    } else {
      valid_steer_req_count = MIN(valid_steer_req_count + 1, limits.min_valid_request_frames);
      invalid_steer_req_count = 0;
    }
  }

  // reset to 0 if either controls is not allowed or there's a violation
  if (violation || !is_lat_active()) {
    valid_steer_req_count = 0;
    invalid_steer_req_count = 0;
    desired_torque_last = 0;
    rt_torque_last = 0;
    ts_torque_check_last = ts;
    ts_steer_req_mismatch_last = ts;
  }

  return violation;
}

// Safety checks for angle-based steering commands
bool steer_angle_cmd_checks(int desired_angle, bool steer_control_enabled, const AngleSteeringLimits limits) {
  bool violation = false;

  if (is_lat_active() && steer_control_enabled) {
    // convert floating point angle rate limits to integers in the scale of the desired angle on CAN,
    // add 1 to not false trigger the violation. also fudge the speed by 1 m/s so rate limits are
    // always slightly above openpilot's in case we read an updated speed in between angle commands
    // TODO: this speed fudge can be much lower, look at data to determine the lowest reasonable offset
    const float fudged_speed = (vehicle_speed.min / VEHICLE_SPEED_FACTOR) - 1.;
    int delta_angle_up = (interpolate(limits.angle_rate_up_lookup, fudged_speed) * limits.angle_deg_to_can) + 1.;
    int delta_angle_down = (interpolate(limits.angle_rate_down_lookup, fudged_speed) * limits.angle_deg_to_can) + 1.;

    // allow down limits at zero since small floats from openpilot will be rounded to 0
    // TODO: openpilot should be cognizant of this and not send small floats
    int highest_desired_angle = desired_angle_last + ((desired_angle_last > 0) ? delta_angle_up : delta_angle_down);
    int lowest_desired_angle = desired_angle_last - ((desired_angle_last >= 0) ? delta_angle_down : delta_angle_up);

    // check that commanded angle value isn't too far from measured, used to limit torque for some safety modes
    // ensure we start moving in direction of meas while respecting relaxed rate limits if error is exceeded
    if (limits.enforce_angle_error && ((vehicle_speed.values[0] / VEHICLE_SPEED_FACTOR) > limits.angle_error_min_speed)) {
      // flipped fudge to avoid false positives
      const float fudged_speed_error = (vehicle_speed.max / VEHICLE_SPEED_FACTOR) + 1.;
      const int delta_angle_up_relaxed = (interpolate(limits.angle_rate_up_lookup, fudged_speed_error) * limits.angle_deg_to_can) - 1.;
      const int delta_angle_down_relaxed = (interpolate(limits.angle_rate_down_lookup, fudged_speed_error) * limits.angle_deg_to_can) - 1.;

      // the minimum and maximum angle allowed based on the measured angle
      const int lowest_desired_angle_error = angle_meas.min - limits.max_angle_error - 1;
      const int highest_desired_angle_error = angle_meas.max + limits.max_angle_error + 1;

      // the MAX is to allow the desired angle to hit the edge of the bounds and not require going under it
      if (desired_angle_last > highest_desired_angle_error) {
        const int delta = (desired_angle_last >= 0) ? delta_angle_down_relaxed : delta_angle_up_relaxed;
        highest_desired_angle = MAX(desired_angle_last - delta, highest_desired_angle_error);

      } else if (desired_angle_last < lowest_desired_angle_error) {
        const int delta = (desired_angle_last <= 0) ? delta_angle_down_relaxed : delta_angle_up_relaxed;
        lowest_desired_angle = MIN(desired_angle_last + delta, lowest_desired_angle_error);

      } else {
        // already inside error boundary, don't allow commanding outside it
        highest_desired_angle = MIN(highest_desired_angle, highest_desired_angle_error);
        lowest_desired_angle = MAX(lowest_desired_angle, lowest_desired_angle_error);
      }

      // don't enforce above the max steer
      // TODO: this should always be done
      lowest_desired_angle = CLAMP(lowest_desired_angle, -limits.max_angle, limits.max_angle);
      highest_desired_angle = CLAMP(highest_desired_angle, -limits.max_angle, limits.max_angle);
    }

    // check not above ISO 11270 lateral accel assuming worst case road roll
    if (limits.angle_is_curvature) {

      // Limit to average banked road since safety doesn't have the roll
      static const float MAX_LATERAL_ACCEL = ISO_LATERAL_ACCEL - (EARTH_G * AVERAGE_ROAD_ROLL);  // ~2.4 m/s^2

      // Allow small tolerance by using minimum speed and rounding curvature up
      const float speed_lower = MAX(vehicle_speed.min / VEHICLE_SPEED_FACTOR, 1.0);
      const float speed_upper = MAX(vehicle_speed.max / VEHICLE_SPEED_FACTOR, 1.0);
      const int max_curvature_upper = (MAX_LATERAL_ACCEL / (speed_lower * speed_lower) * limits.angle_deg_to_can) + 1.;
      const int max_curvature_lower = (MAX_LATERAL_ACCEL / (speed_upper * speed_upper) * limits.angle_deg_to_can) - 1.;

      // ensure that the curvature error doesn't try to enforce above this limit
      if (desired_angle_last > 0) {
        lowest_desired_angle = CLAMP(lowest_desired_angle, -max_curvature_lower, max_curvature_lower);
        highest_desired_angle = CLAMP(highest_desired_angle, -max_curvature_upper, max_curvature_upper);
      } else {
        lowest_desired_angle = CLAMP(lowest_desired_angle, -max_curvature_upper, max_curvature_upper);
        highest_desired_angle = CLAMP(highest_desired_angle, -max_curvature_lower, max_curvature_lower);
      }
    }

    // check for violation;
    violation |= max_limit_check(desired_angle, highest_desired_angle, lowest_desired_angle);
  }
  desired_angle_last = desired_angle;

  // Angle should either be 0 or same as current angle while not steering
  if (!steer_control_enabled) {
    const int max_inactive_angle = CLAMP(angle_meas.max, -limits.max_angle, limits.max_angle) + 1;
    const int min_inactive_angle = CLAMP(angle_meas.min, -limits.max_angle, limits.max_angle) - 1;
    violation |= (limits.inactive_angle_is_zero ? (desired_angle != 0) :
                  max_limit_check(desired_angle, max_inactive_angle, min_inactive_angle));
  }

  // No angle control allowed when controls are not allowed
  violation |= !is_lat_active() && steer_control_enabled;

  return violation;
}

static float get_curvature_factor(const float speed, const AngleSteeringParams params) {
  return 1. / (1. - (params.slip_factor * (speed * speed))) / params.wheelbase;
}

bool steer_angle_cmd_checks_vm(int desired_angle, bool steer_control_enabled, const AngleSteeringLimits limits,
                               const AngleSteeringParams params) {
  // This check uses a simple vehicle model to allow for true lateral acceleration and jerk limits.
  // TODO: remove the inaccurate breakpoint angle limiting function above and always use this one

  static const float RAD_TO_DEG = 57.29577951308232;

  // Highway curves are rolled in the direction of the turn, add tolerance to compensate
  static const float MAX_LATERAL_ACCEL = ISO_LATERAL_ACCEL + (EARTH_G * AVERAGE_ROAD_ROLL);  // ~3.6 m/s^2
  // Lower than ISO 11270 lateral jerk limit, which is 5.0 m/s^3
  static const float MAX_LATERAL_JERK = 3.0 + (EARTH_G * AVERAGE_ROAD_ROLL);  // ~3.6 m/s^3

  const float fudged_speed = (vehicle_speed.min / VEHICLE_SPEED_FACTOR) - 1.;
  const float curvature_factor = get_curvature_factor(fudged_speed, params);

  bool violation = false;

  if (is_lat_active() && steer_control_enabled) {
    // *** ISO lateral jerk limit ***
    // calculate maximum angle rate per second
    const float speed = MAX(fudged_speed, 1.0);
    const float max_curvature_rate_sec = MAX_LATERAL_JERK / (speed * speed);
    const float max_angle_rate_sec = max_curvature_rate_sec * params.steer_ratio / curvature_factor * RAD_TO_DEG;

    // finally get max angle delta per frame
    const float max_angle_delta = max_angle_rate_sec * (0.01f * 2.0f);  // 50 Hz
    const int max_angle_delta_can = (max_angle_delta * limits.angle_deg_to_can) + 1.;

    // NOTE: symmetric up and down limits
    const int highest_desired_angle = desired_angle_last + max_angle_delta_can;
    const int lowest_desired_angle = desired_angle_last - max_angle_delta_can;

    violation |= max_limit_check(desired_angle, highest_desired_angle, lowest_desired_angle);

    // *** ISO lateral accel limit ***
    const float max_curvature = MAX_LATERAL_ACCEL / (speed * speed);
    const float max_angle = max_curvature * params.steer_ratio / curvature_factor * RAD_TO_DEG;
    const int max_angle_can = (max_angle * limits.angle_deg_to_can) + 1.;

    violation |= max_limit_check(desired_angle, max_angle_can, -max_angle_can);
  }
  desired_angle_last = desired_angle;

  // Angle should either be 0 or same as current angle while not steering
  if (!steer_control_enabled) {
    const int max_inactive_angle = CLAMP(angle_meas.max, -limits.max_angle, limits.max_angle) + 1;
    const int min_inactive_angle = CLAMP(angle_meas.min, -limits.max_angle, limits.max_angle) - 1;
    violation |= (limits.inactive_angle_is_zero ? (desired_angle != 0) :
                  max_limit_check(desired_angle, max_inactive_angle, min_inactive_angle));
  }

  // No angle control allowed when controls are not allowed
  violation |= !is_lat_active() && steer_control_enabled;

  return violation;
}

void pcm_cruise_check(bool cruise_engaged) {
  // Enter controls on rising edge of stock ACC, exit controls if stock ACC disengages
  if (!cruise_engaged) {
    controls_allowed = false;
  }
  if (cruise_engaged && !cruise_engaged_prev) {
    controls_allowed = true;
  }
  cruise_engaged_prev = cruise_engaged;
}

void speed_mismatch_check(const float speed_2) {
  // Disable controls if speeds from two sources are too far apart.
  // For safety modes that use speed to adjust torque or angle limits
  const float MAX_SPEED_DELTA = 2.0;  // m/s
  bool is_invalid_speed = ABS(speed_2 - ((float)vehicle_speed.values[0] / VEHICLE_SPEED_FACTOR)) > MAX_SPEED_DELTA;
  if (is_invalid_speed) {
    controls_allowed = false;
  }
}
