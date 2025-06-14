#include <stdio.h>

void safety_tick_current_safety_config() {
  safety_tick(&current_safety_config);
}

bool safety_config_valid() {
  if (current_safety_config.rx_checks_len <= 0) {
    printf("missing RX checks\n");
    return false;
  }

  for (int i = 0; i < current_safety_config.rx_checks_len; i++) {
    const RxCheck addr = current_safety_config.rx_checks[i];
    bool valid = addr.status.msg_seen && !addr.status.lagging && addr.status.valid_checksum && (addr.status.wrong_counters < MAX_WRONG_COUNTERS) && addr.status.valid_quality_flag;
    if (!valid) {
      // printf("i %d seen %d lagging %d valid checksum %d wrong counters %d valid quality flag %d\n", i, addr.status.msg_seen, addr.status.lagging, addr.status.valid_checksum, addr.status.wrong_counters, addr.status.valid_quality_flag);
      return false;
    }
  }
  return true;
}


static MADSState *get_mads_state(void) {
  return &m_mads_state;
}

void set_controls_allowed(bool c){
  controls_allowed = c;
}

void set_alternative_experience(int mode){
  alternative_experience = mode;
}

void set_relay_malfunction(bool c){
  relay_malfunction = c;
}

bool get_controls_allowed(void){
  return controls_allowed;
}

bool get_lat_active(void){
  return is_lat_active();
}

bool get_controls_allowed_lat(void){
  return mads_is_lateral_control_allowed_by_mads();
}

bool get_controls_requested_lat(void){
  return get_mads_state()->controls_requested_lat;
}

bool get_enable_mads(void){
  return get_mads_state()->system_enabled;
}

bool get_disengage_lateral_on_brake(void){
  return get_mads_state()->disengage_lateral_on_brake;
}

bool get_pause_lateral_on_brake(void){
  return get_mads_state()->pause_lateral_on_brake;
}

int get_alternative_experience(void){
  return alternative_experience;
}

bool get_relay_malfunction(void){
  return relay_malfunction;
}

bool get_gas_pressed_prev(void){
  return gas_pressed_prev;
}

void set_gas_pressed_prev(bool c){
  gas_pressed_prev = c;
}

bool get_brake_pressed_prev(void){
  return brake_pressed_prev;
}

bool get_regen_braking_prev(void){
  return regen_braking_prev;
}

bool get_steering_disengage_prev(void){
  return steering_disengage_prev;
}

bool get_cruise_engaged_prev(void){
  return cruise_engaged_prev;
}

void set_cruise_engaged_prev(bool engaged){
  cruise_engaged_prev = engaged;
}

bool get_vehicle_moving(void){
  return vehicle_moving;
}

bool get_acc_main_on(void){
  return acc_main_on;
}

float get_vehicle_speed_min(void){
  return vehicle_speed.min / VEHICLE_SPEED_FACTOR;
}

float get_vehicle_speed_max(void){
  return vehicle_speed.max / VEHICLE_SPEED_FACTOR;
}

void set_acc_main_on(bool c){
  acc_main_on = c;
}

int get_current_safety_mode(void){
  return current_safety_mode;
}

int get_current_safety_param(void){
  return current_safety_param;
}

void set_current_safety_param_sp(int param){
  current_safety_param_sp = param;
}

int get_current_safety_param_sp(void){
  return current_safety_param_sp;
}

void set_timer(uint32_t t){
  timer.CNT = t;
}

void set_torque_meas(int min, int max){
  torque_meas.min = min;
  torque_meas.max = max;
}

int get_torque_meas_min(void){
  return torque_meas.min;
}

int get_torque_meas_max(void){
  return torque_meas.max;
}

void set_torque_driver(int min, int max){
  torque_driver.min = min;
  torque_driver.max = max;
}

int get_torque_driver_min(void){
  return torque_driver.min;
}

int get_torque_driver_max(void){
  return torque_driver.max;
}

void set_rt_torque_last(int t){
  rt_torque_last = t;
}

void set_desired_torque_last(int t){
  desired_torque_last = t;
}

void set_desired_angle_last(int t){
  desired_angle_last = t;
}

int get_desired_angle_last(void){
  return desired_angle_last;
}

void set_angle_meas(int min, int max){
  angle_meas.min = min;
  angle_meas.max = max;
}

int get_angle_meas_min(void){
  return angle_meas.min;
}

int get_angle_meas_max(void){
  return angle_meas.max;
}


// ***** car specific helpers *****

void set_honda_alt_brake_msg(bool c){
  honda_alt_brake_msg = c;
}

void set_honda_bosch_long(bool c){
  honda_bosch_long = c;
}

int get_honda_hw(void) {
  return honda_hw;
}

void set_honda_fwd_brake(bool c){
  honda_fwd_brake = c;
}

bool get_honda_fwd_brake(void){
  return honda_fwd_brake;
}

void set_mads_button_press(int c){
  mads_button_press = c;
}

int get_mads_button_press(void){
  return mads_button_press;
}

void set_controls_allowed_lat(bool c){
  m_mads_state.controls_allowed_lat = c;
}

bool get_mads_acc_main(void){
  return m_mads_state.acc_main.current;
}

int mads_get_current_disengage_reason(void) {
  return get_mads_state()->current_disengage.active_reason;
}

void mads_set_current_disengage_reason(int reason) {
  m_mads_state.current_disengage.active_reason = reason;
}

void set_controls_requested_lat(bool c){
  m_mads_state.controls_requested_lat = c;
}

void set_mads_params(bool enable_mads, bool disengage_lateral_on_brake, bool pause_lateral_on_brake){
  alternative_experience = 0;
  if (enable_mads) {
    alternative_experience |= ALT_EXP_ENABLE_MADS;

    if (disengage_lateral_on_brake) {
      alternative_experience |= ALT_EXP_MADS_DISENGAGE_LATERAL_ON_BRAKE;
    } else if (pause_lateral_on_brake) {
      alternative_experience |= ALT_EXP_MADS_PAUSE_LATERAL_ON_BRAKE;
    } else {
    }
  }

  mads_set_alternative_experience(&alternative_experience);
}

void set_heartbeat_engaged_mads(bool c){
  heartbeat_engaged_mads = c;
}

void set_steering_disengage(bool c){
  steering_disengage = c;
}

//int get_temp_debug(void){
//  return temp_debug;
//}

void init_tests(void){
  safety_mode_cnt = 2U;  // avoid ignoring relay_malfunction logic
  alternative_experience = 0;
  current_safety_param_sp = 0;
  set_timer(0);
  ts_steer_req_mismatch_last = 0;
  valid_steer_req_count = 0;
  invalid_steer_req_count = 0;

  // assumes autopark on safety mode init to avoid a fault. get rid of that for testing
  tesla_autopark = false;
}
