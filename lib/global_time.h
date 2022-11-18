
#ifndef __GLOBAL_TIME__
#define __GLOBAL_TIME__

// Time since startup
// This is stored as a 32 bit number, meaning it would only overflow after 49.7 days
// Which is more than enough tbh
extern uint32_t global_time;

// Initialize the timer
void setup_global_timer();

#endif
