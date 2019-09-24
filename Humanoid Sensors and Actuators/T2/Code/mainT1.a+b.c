#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif
#include <util/delay.h>
#include <atmega32/uart.h>


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
    *b = (uint8_t)ADCL;		// Read low byte
    *b = (uint8_t)ADCH;		// Read high byte

}


int main (void)
{            
    ADC_Init();
    uint8_t AD_C;
    //DDRC  = 0xFF;

    uart_setBaudrateReg(CALC_BAUD_VAL(62500)); // 15
    uart_setFormat();
    uart_enable();
    uint8_t a;

    while(1){
        adc_readBlocking((uint8_t*)&AD_C,1); // read from adc to var AD_C
        a= AD_C;
        uart_writeBlocking((uint8_t*)&a,1); // transmit var a over serial connection

    }
    return 0;
}
