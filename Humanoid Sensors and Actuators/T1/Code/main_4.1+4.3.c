#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

#include <util/delay.h>

#define BAUD_PRESCALE 0 // (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) = 0 in our case!!

unsigned char Recieve_Char()
{
    while ((UCSRA & (1 << RXC)) == 0);// Wait until data is fully received
    return(UDR);			// Get and return received data from buffer
}

void Send_Char(char ch)
{
    while (! (UCSRA & (1<<UDRE)));	// Wait for an empty transmit buffer
    UDR = ch ;
}

void Send_String(char *str)
{
    unsigned char i=0;

    while (str[i]!=0)
    {
        Send_Char(str[i]);
        i++;
    }
}

int main()
{
    //initialize UART

    UCSRB |= (1 << RXEN) | (1 << TXEN);// Turn on transmission and reception
    //UCSRC = no need to be changed because standard frame is 8data,1stop, no parity
    UBRRL = BAUD_PRESCALE; // Load low byte of prescaler into prescaler-register
    UBRRH = (BAUD_PRESCALE >> 8);	// Load upper byte


    char c;
    while(1)
    {
        //c=Recieve_Char();
        //Send_Char(c);// these two lines allow for the echo function! 4.1


        Send_String("Hello World!"); // these two lines allow sending a string with 1HZ Frequency 4.2 4.3
        _delay_ms(1000);
    }
}
