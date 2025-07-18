#include "opendbc/safety/safety.h"

// this file is checked by cppcheck

// Ignore misra-c2012-8.7 as these functions are only called from panda and libsafety
UNUSED(heartbeat_engaged);

UNUSED(safety_rx_hook);
UNUSED(safety_tx_hook);
UNUSED(safety_fwd_hook);
UNUSED(safety_tick);
UNUSED(set_safety_hooks);
UNUSED(mads_heartbeat_engaged_check);
UNUSED(mads_set_alternative_experience);
UNUSED(get_acc_main_on_mismatches);
