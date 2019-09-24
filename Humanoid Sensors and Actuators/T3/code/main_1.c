#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif
#include <avr/interrupt.h>
#include <util/delay.h>          

volatile uint8_t C;
ISR(TIMER2_OVF_vect){
    C= C+1;
    if(C== 60){//1second

        PORTC = !PORTC;
        C=0;
    }
}


int main (void)
{            
    cli(); // disable all interrupts
    DDRC |= 0x01;
    TCCR2 |= (1<<CS22)  ; //intialize the time clock prescaler to 64
    TCCR2 &= ~((1<<CS21) | (1<< CS20));
    TIMSK |= (1<<TOIE2);    //overflow interrupt enable
    TCNT2 = 0; // init register counter to 0
    C= 0;
    sei(); // enable interrupts
    PORTC |= (1<<PC0); //set PC0 as desired output pin
    while(1){           //dummy infinite loop

        //if (C == 0xFF) PORTC |= (1<<PC0); else PORTC &= ~(1<<PC0);
    }
    return 0;
}
