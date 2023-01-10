
#include <avr/io.h>
#include <brightness.h>

void init_adc()
{
    DDRC &= ~(1 << DDC0);     // Set A0 as input pin
    
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // Prescaler 128
	ADMUX |= (1 << REFS0); // Rev vcc
	ADCSRA |= (1<<ADEN); 
    ADCSRA |= (1<<ADATE); // auto trigger
    ADCSRA |= (1<<ADSC); // start
}

void init_pwm()
{
    OCR2B = 255;

    DDRD |= (1 << PD3); // Set pin PD3 as output

    // Set fast PWM mode on Timer1
    
    TCCR2A |= (1 << WGM20);
    TCCR2A |= (1 << WGM21);

    TCCR2A |= (1 << COM2B1);
    TCCR2A |= (1 << COM2A1);

    TCCR2B |= (1 << CS21); // Set prescaler to 256
    TCCR2B |= (1 << CS22); // Set prescaler to 256
}
