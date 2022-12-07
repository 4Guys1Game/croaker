
#ifndef __IR__
#define __IR__

#define FREQ_VAL_38KHZ 105
#define FREQ_VAL_56KHZ 71

// A message only containing 5 bits
typedef uint8_t IRData;

extern uint8_t packet_sent;

IRData ir_get_latest_data_packet();

void ir_send_message(IRData data);

// Initializes the pins for generating IR signals
// You have to give a frequency to configure it properly
// Use either FREQ_VAL_38KHZ or FREQ_VAL_56KHZ
void init_ir(uint8_t frequency);

// Invoke this the main loop
void ir_heartbeat();

#endif
