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
                            //1st method
    in r23, DDRC
    ori r23, 0x07
    out DDRC, r23

 loop:
    in r21, PORTC           //1 CPU
    ori r21, 0x01           //1 CPU
    andi r21, 0xFB          //1 CPU
    out PORTC, r21          //1 CPU, 4 CPU in total for one step
    rcall delay

    in r21, PORTC
    ori r21, 0x02
    andi r21, 0xFE
    out PORTC, r21
    rcall delay

    in r21, PORTC
    ori r21, 0x04
    andi r21, 0xFD
    out PORTC, r21
    rcall delay

    rjmp loop

                            //2rd method
//    sbi PORTC, 0;         //2 CPU
//    cbi PORTC, 2          //2 CPU, 4 CPU in total for one step
//    rcall delay
//    sbi PORTC, 1
//    cbi PORTC, 0
//    rcall delay
//    sbi PORTC, 2
//    cbi PORTC, 1;
//    rcall delay

//    rjmp loop ;

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



    ret                         //exit (never reached)

.end


