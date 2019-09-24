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

    sbi DDRC, 0;    //set output of pin 0 on DDRC to high

 rep:
    sbi PORTC, 0;   //set ouput of pin 0 on port C to high
    ldi r18, 0x3F   //wait for one second
    ldi r24, 0x0D
    ldi r25, 0x03
 1: subi r18, 0x01
    sbci r24, 0x00
    sbci r25, 0x00
    brne 1b
    rjmp 1f
 1: nop

    cbi PORTC, 0;   //set output of pin 0 on port C to low
    ldi r18, 0x3F   //wait for one second
    ldi r24, 0x0D
    ldi r25, 0x03
 2: subi r18, 0x01
    sbci r24, 0x00
    sbci r25, 0x00
    brne 2b
    rjmp 2f
 2: nop
    rjmp rep        //repeat the loop

    ret             //exit (never reached)

.end


