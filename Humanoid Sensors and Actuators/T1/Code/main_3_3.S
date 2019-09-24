// to use register names direcly in asm
#define   __SFR_OFFSET  0

#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif


.global main

main:

    sbi DDRC, 0;    //set output of pin 0,1,2 on DDRC to high
    sbi DDRC, 1;
    sbi DDRC, 2;

 loop:

    sbi PORTC, 0;   //set ouput of pin 0 on port C to high, LED1 on
    cbi PORTC, 2    //set ouput of pin 2 on port C to low, LED3 off
    rcall delay     //delay 1 sec
    sbi PORTC, 1    //LED2 on
    cbi PORTC, 0    //LED1 off
    rcall delay
    sbi PORTC, 2    //LED3 on
    cbi PORTC, 1;   //LED2 off
    rcall delay

    rjmp loop ;     //repeat the loop

 delay:             //function for delay 1 sec

    ldi r18, 0x3F
    ldi r24, 0x0D
    ldi r25, 0x03
 1: subi r18, 0x01
    sbci r24, 0x00
    sbci r25, 0x00
    brne 1b
    rjmp 1f
 1: nop
    ret



    ret              //exit (never reached)

.end


