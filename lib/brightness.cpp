
#include "brightness.h"
#include <avr/io.h>
#include <util/delay.h>

void init_adc()
{
    DDRC &= ~(1 << DDC0);     // Set A0 as input pin
    
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
	ADMUX |= (1 << REFS0); // Rev vcc
	ADCSRA |= (1<<ADEN); 
    ADCSRA |= (1<<ADATE); // auto trigger
    ADCSRA |= (1<<ADSC); // start
    uint8_t result = ADC; // Result

    return 0;
}