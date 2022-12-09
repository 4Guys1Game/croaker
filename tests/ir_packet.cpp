#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <HardwareSerial.h>
#include "ir.h"

// Expected result:
// Each value gets encoded into a packet and then decoded in the correct way
// A line in the console saying convert_packet_to_data: Success if the i and decoded value match, a message saying convert_packet_to_data: Fail if it doesn't
void convert_packet_to_data(){
    for(int i = 0; i < 32; i++){
        //create a packet with i as the data
        uint8_t packet = ir_create_packet(i);
        uint8_t value = convert_packet_to_irdata(packet);
        if(value != i){
            Serial.println("convert_packet_to_data: Fail");
        }
    }
    Serial.println("convert_packet_to_data: Success");
}