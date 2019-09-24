#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

#include <util/delay.h>          

void step_delay(void){
    _delay_ms(200);
}

int main (void)
{            
    DDRC= 0xFF;
    DDRD= 0xFF;


    PORTC = (1<<(PC0));
    while(1){




        PORTD = 0x1E;//phase 1   we will see in next code that the corresponding output is 011 = 3 (from hall sensors)
        step_delay();
        PORTD = 0x1B;//phase 2
        step_delay();
        PORTD = 0x27;//phase 3
        step_delay();
        PORTD = 0x36;//phase 4
        step_delay();
        PORTD = 0x39;//phase 5
        step_delay();
        PORTD = 0x2D;//phase 6
        step_delay();
		
		
    }
    return 0;
}
