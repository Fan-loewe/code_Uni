#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

#include <util/delay.h>
void read_hall(void);
uint8_t my_value;

void step_delay(void){

    _delay_ms(40);
    read_hall();
    _delay_ms(2500);
}

void read_hall(void){

    my_value = PINC & 0x07;
    PORTA = my_value; // show by turning on LEDs
}

    int main (void)
{
    DDRC= 0xF0;
    DDRD= 0xFF;
    DDRA= 0xFF;

    PORTC = (1<<(PC0) | (1<<(PC1)) | (1<<(PC2) )) ; // write 1s to the pins to switch the pull-up resistors on

	//initializations 
    _delay_ms(2000);
    PORTC |= (1<<(PC7));
    PORTD = 0x2D;//phase 1
    read_hall();
    while(1){

        read_hall();


        // 3 , 1 , 5 , 4, 6, 2 correspondance phase 1:6 --> my_value(hall sensor)



        // clockwise direction
        /*if(my_value ==2){ PORTB = 0x2D;//phase 1   ___>  3 (corresponds to value 3 from hall sensors)
        read_hall();}
        else if(my_value ==3){ PORTB = 0x27;//phase 2 ___>1
        read_hall();}
        else if(my_value ==1){PORTB = 0x1B;//phase 3 ___>5
        read_hall();}
        else if(my_value ==5){PORTB = 0x39;//phase 4 ___>4
        read_hall();}
        else if(my_value ==4){PORTB = 0x36;//phase 5 ___>6
        read_hall();}
        else if (my_value ==6){PORTB = 0x1E;//phase 6 ___>2
        read_hall();}
        else PORTD = 0x2D;*/




        //counterclockwise direction
        if(my_value ==1){ PORTB  = 0x2D;//phase 1 ___>3
        read_hall();}
        else if(my_value ==5){ PORTB = 0x27;//phase 2 ___>1
        read_hall();}
        else if(my_value ==4){PORTB = 0x1B;//phase 3 ___>5
        read_hall();}
        else if(my_value ==6){PORTB = 0x39;//phase 4 ___>4
        read_hall();}
        else if(my_value ==2){PORTB = 0x36;//phase 5 ___>6
        read_hall();}
        else if (my_value ==3){PORTB = 0x1E;//phase 6 ___>2
        read_hall();}
        else PORTD = 0x2D;

    }
    return 0;
}
