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

    sbi DDRC, 0;        //set output of pin 0,1,2,3 on DDRC to high, as output
    sbi DDRC, 1;
    sbi DDRC, 2;
    sbi DDRC, 3;
    cbi DDRC, 4;        //set output of pin 4 on DDRC to low, as input

 loop:

sbic PINC, 4;           //if bit of pin4 is cleared, skip to nop; otherwise, go to next step
    rjmp set1           //set bit of pin3
    nop
    nop

sbis PINC, 4;           //if bit of pin4 is set, skip to nop; otherwise, go to next step
    rjmp set2           //clear bit of pin3
    nop
    nop

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

 set1:                      //function to set bit of pin3(delay 1 sec)
    rcall delay
    sbi PORTC, 3;
    rjmp loop;


 set2:                      //function to clear bit of pin3(delay 1 sec)
    rcall delay
    cbi PORTC, 3;
    rjmp loop;


    ret                      //exit (never reached)

.end


