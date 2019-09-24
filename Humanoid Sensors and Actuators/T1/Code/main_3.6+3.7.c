#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

#include <util/delay.h>          


int main (void)
{            
    DDRC |= 0x07 ;        //set output of bit 0,1,2 on DDRC to high
    while(1){
        PORTC |= 0x01;    //set ouput of pin 0 on port C to high
        _delay_ms(1000);
        PORTC &= ~0x01;   //set output of pin 0 on port C to low
        _delay_ms(1000);
    }

    return 0;
}
