// to use register names direcly in asm
#define   __SFR_OFFSET  0

#ifndef __AVR_ATmega32__
    #include <avr/iom32.h>
    #error "__FILE__ the CPU you selected is not supported."
#else
    #include <avr/io.h>
#endif

.global add512

add512:

// ptr to a is in R23:R22
// ptr to b is in R21:R20
// ptr to c is in R25:R24
    mov r26,r22         //move the value of a,b,c to X,Y,Z
    mov r27,r23

    mov r28,r20
    mov r29,r21

    mov r30,r24
    mov r31,r25

    ldi r22,0x40;         //set the number of loop 64=512/8
    clc                   //clear carry before first iteration

    loop:
    ld r18,X+             //use X,Y,Z to do the addition with carry
    ld r19,Y+
    adc r19,r18
    st Z+,r19
    brcs flagger          //if carry is set jump to flagger
    subi r22, 0x01        //otherwise continue

    res:                  //resume
    breq ender;           //if the loop execute 64 times then leave loop
    rjmp loop             //otherwise go back to the loop


    flagger:
    subi r22, 0x01        //loop number subtract one
    sec                   //set carry again
    rjmp res

    ender:
    nop
    ret
.end


