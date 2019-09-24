#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif
#include <avr/interrupt.h>
#include <util/delay.h>
#include <atmega32/uart.h>

void read_hall(void);
volatile uint8_t Glob_State;
volatile uint8_t my_value;
uint16_t timer_count ;
uint8_t i;

void ADC_Init(void)
{
    DDRA=0x0;			// Make ADC port as input
    ADCSRA |= (1<<ADEN) | (1<<ADPS0);	// Enable ADC, factor = 2
    ADMUX |= (1<<REFS0) | (1<<ADLAR) ;	// Vref: Avcc, left adjusted for 8 bit
    SFIOR &= ~((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2)); //free running mode

}

void adc_readBlocking(uint8_t* b,uint8_t ch)
{

    ADMUX=ADMUX|(ch );	// Set input channel to read

    ADCSRA |= (1<<ADSC);		// Start conversion
    while( ! (ADCSRA&(1<<ADSC) ) ); // wait until conversion is done
    *b = (uint8_t)ADCL;		// Read high byte
    *b = (uint8_t)ADCH;		// Read high byte

}


void step_delay(void){

    _delay_ms(2);
    read_hall();
    _delay_ms(1500);
}

void read_hall(void){

        my_value = PINC & 0x07;

}

ISR(TIMER0_OVF_vect	) // Interrupt service routine for TIMER2 overflow Interrupt
{
    Glob_State = 0;

    //TCNT2 = 0;

    timer_count = timer_count+1;

    adc_readBlocking(&i,0); // read from channel 0
    //if(i > 250) i= 250;  // limits for max and min allowed values
    //else if(i< 5) i= 5;
    PORTC &= ~(1<<(PC7));

}

ISR(TIMER0_COMP_vect) // Interrupt service routine for TIMER2 COMPARE Interrupt
{
    Glob_State = 1;


    PORTC |= (1<<(PC7));

//TCNT2 = 0;

}

    int main (void)
{
    cli(); // disable all interrupts
    Glob_State = 0;
	my_value = 3;
    timer_count=0;
    i=0;
    uint8_t j = 0;
    uint8_t phase_seq[] = {3,1,5,4,6,2};// this is the order of phase states which corresponds to 1 rotation
    uint8_t speed = 0;
    float k = 0.0;
    uint16_t rotations =0;
    DDRB = 0x3F;
    DDRA = 0x00;			// Make ADC port as input
    DDRC= 0xF0; // half read half write
    PORTC = (1<<(PC0) | (1<<(PC1)) | (1<<(PC2) )) ; // write 1s to the pins to switch the pull-up resistors on




    TCCR0 |= ( (1<<CS00) );//  |(1<<CS01));		//timer2 is used for the output compare interrupt, prescale is 1
    TCCR0 &= ~( (1<<CS02) | (1<< CS01) );//| (1<<FOC2) |(1<<COM20) );
    TIMSK |= (1<<OCIE0); // compare match interrupt
    TIMSK |= (1<<TOIE0);//for overflow
    TCNT0 = 0; // init register counter to 0

    OCR0 = 126; // initialize value to compare to

	ADC_Init();

    uart_setBaudrateReg(CALC_BAUD_VAL(62500)); // 15
    uart_setFormat();
    uart_enable();
	
    sei(); // enable interrupts


    _delay_ms(2000);
    PORTC |= (1<<(PC7));// LED for debug
    //PORTB = 0b00101101;//phase 1
    read_hall();

    while(1){

        read_hall();
        OCR0 = i; // 230 =  %10DC, 192= 25%DC, 128= 50%DC, 64= 25%DC, 0= 100%DC


        // 3 , 1 , 5 , 4, 6, 2


        switch(my_value){
            case 2:
            PORTB = 0b00101001 | (Glob_State << 2);
            break;

            case 3:
            PORTB = 0b00100110 | (Glob_State << 0);
            break;

            case 1:
            PORTB = 0b00011010 | (Glob_State << 0);
            break;

            case 5:
            PORTB = 0b00101001 | (Glob_State << 4);
            break;

            case 4:
            PORTB = 0b00100110 | (Glob_State << 4);
            break;

            case 6:
            PORTB = 0b00011010 | (Glob_State << 2);
            break;

        }


        if(timer_count >= 3906){ // corresponds to 1 second
            k = (rotations/4.0 ); // because 4 pole pairs
            if(k>254){
                speed=255; // in order to tell if value out of range
            }else{
            speed = (uint8_t)(k);

            }
            timer_count= 0;
            rotations=0;
            uart_writeBlocking((uint8_t*)&speed,1);
        } else if(my_value == phase_seq[j] && j < 6){ // run through all phases

            j++;
        }else if(j>=6){// if all phases satisfied ==> 1 pole pair rotation
            j=0;
            rotations++;

        }



        /*
         * T3.2.7

        PORTB = 0b00101001 | (Glob_State << 2);//phase 1
        step_delay();
        PORTB = 0b00100110 | (Glob_State << 0);//phase 2
        step_delay();
        PORTB = 0b00011010 | (Glob_State << 0);//phase 3
        step_delay();
        PORTB = 0b00101001 | (Glob_State << 4);//phase 4
        step_delay();
        PORTB = 0b00100110 | (Glob_State << 4);//phase 5
        step_delay();
        PORTB = 0b00011010 | (Glob_State << 2);//phase 6
        step_delay();
        */





    }
    return 0;
}
