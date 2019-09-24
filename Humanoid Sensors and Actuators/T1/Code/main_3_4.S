// to use register names direcly in asm
#define   __SFR_OFFSET  0

#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif


.global main             //second way to achieve the task

main:


    in r23, DDRC        //set output of pin 0,1,2 on DDRC to high, as output
    ori r23, 0x07
    out DDRC, r23

 loop:
    in r21, PORTC
    ori r21, 0x01       //set output of pin 0 on port C to high, LED1 on
    andi r21, 0xFB      //set ouput of pin 2 on port C to low, LED3 on
    out PORTC, r21
    rcall delay         //delay 1 sec

    in r21, PORTC
    ori r21, 0x02       //LED2 on
    andi r21, 0xFE      //LED1 off
    out PORTC, r21
    rcall delay

    in r21, PORTC
    ori r21, 0x04       //LED3 on
    andi r21, 0xFD      //LED2 off
    out PORTC, r21
    rcall delay         //repeat the loop

    rjmp loop


 delay:

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



    ret                   //exit (never reached)

.end


