#include <avr/io.h>
#include <util/delay.h>          

#include <atmega32/uart.h>
#include <atmega32/adc.h>

int main (void)
{            
    DDRC  = 0xFF;

    uart_setBaudrateReg(CALC_BAUD_VAL(62500)); // 15
    uart_setFormat();
    uart_enable();

    adc_setStdConfig(); // prescaler 2 ==> max frequency
    adc_enable();

    PORTC |= (1 << PC0);
    uint16_t i;
    uint8_t val[1024]; // automatically allocate memory to SRAM
    for(i=0;i<1024;i++) // read in this loop
    {
        //_delay_ms(1);

        adc_readBlocking(&val[i],0); // read from channel 0
    }
    PORTC &= ~(1 << PC0);

    for(i=0;i<4;i++){ // transmit in this loop

    _delay_ms(10);
    uart_writeBlocking(&val[255*i], 255); // send in blocks of 255,
    }// last 4 bytes can be ignored
    // or use this here uart_writeBlocking(&val[1020], 4);
    PORTC &= ~(1 << PC0);
    return 0;
}
