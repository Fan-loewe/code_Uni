#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

#include <util/delay.h>          


int main (void)
{            
    DDRC |= 0x0F;           // set first 4 bits as outputs
    DDRC &= 0xEF;           // set 5th bit (4th pin) as input leaving the others unchanged
    while(1){

        if (PINC & (1<<PC4))//if pin4 is high
        {
            _delay_ms(1000);
            PORTC |= (1<<PC3);

        }
        else
        {
            _delay_ms(1000);
            PORTC &= ~(1<<PC3);


        }

    }
    return 0;
}
