#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif
#include <avr/interrupt.h>
#include <util/delay.h>          


void ADC_Init(void)
{
    DDRA=0x0;			// Make ADC port as input
    ADCSRA |= (1<<ADEN) | (1<<ADPS0);	// Enable ADC, prescaler = 2
    ADMUX |= (1<<REFS0) | (1<<ADLAR) ;	// Vref: Avcc, left adjusted for 8 bit
    SFIOR &= ~((1<<ADTS0) | (1<<ADTS1) | (1<<ADTS2)); //free running mode

}

void adc_readBlocking(uint8_t* b,uint8_t ch)
{

    ADMUX=ADMUX|(ch );	// Set input channel to read

    ADCSRA |= (1<<ADSC);		// Start conversion
    while( ! (ADCSRA&(1<<ADSC) ) ); // wait until conversion is done
    *b = (uint8_t)ADCH;		// Read high byte

}

int main (void)
{            
    cli(); // disable all interrupts
    DDRB |= (1<<PB3);//set OC0(PB3) as PWM output

    ADC_Init();

    TCCR0 |= ((1<<WGM01) | (1<<WGM00) |(1<<CS01) | (1<<COM01) );    //set prescaler as 8(CS01), set fast PWM(WGM01,WGM00), choose compare match mode(COM01)
    //TCCR0 &= ~((1<<CS02) | (1<< CS00) | (1<<FOC0) |(1<<COM00) );
    TCNT0 = 0; // init register counter to 0
    sei(); // enable interrupts

    uint8_t i=0;
    while(1){

        adc_readBlocking(&i,0); // read from channel 0
        OCR0 = i;               // read by ADC as duty cycle for PWM signal
        _delay_ms(10);


    }
    return 0;
}
