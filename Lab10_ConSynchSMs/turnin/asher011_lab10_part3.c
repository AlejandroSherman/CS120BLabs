/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 #include <avr/io.h>
 //#include <avr/interrupt.h>
 //#include <timer.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif

 #include <avr/interrupt.h>

 volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

 // Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
 unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms
 unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

 // Set TimerISR() to tick every M ms
 void TimerSet(unsigned long M) {
     _avr_timer_M = M;
     _avr_timer_cntcurr = _avr_timer_M;
 }

 void TimerOn() {
     // AVR timer/counter controller register TCCR1
     TCCR1B     = 0x0B;    // bit3 = 1: CTC mode (clear timer on compare)
                     // bit2bit1bit0=011: prescaler /64
                     // 00001011: 0x0B
                     // SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
                     // Thus, TCNT1 register will count at 125,000 ticks/s

     // AVR output compare register OCR1A.
     OCR1A     = 125;    // Timer interrupt will be generated when TCNT1==OCR1A
                     // We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
                     // So when TCNT1 register equals 125,
                     // 1 ms has passed. Thus, we compare to 125.
                     // AVR timer interrupt mask register

     TIMSK1     = 0x02; // bit1: OCIE1A -- enables compare match interrupt

     //Initialize avr counter
     TCNT1 = 0;

     // TimerISR will be called every _avr_timer_cntcurr milliseconds
     _avr_timer_cntcurr = _avr_timer_M;

     //Enable global interrupts
     SREG |= 0x80;    // 0x80: 1000000
 }

 void TimerOff() {
     TCCR1B     = 0x00; // bit3bit2bit1bit0=0000: timer off
 }

 void TimerISR() {
     TimerFlag = 1;
 }

 // In our approach, the C programmer does not touch this ISR, but rather TimerISR()
 ISR(TIMER1_COMPA_vect)
 {
     // CPU automatically calls when TCNT0 == OCR0 (every 1 ms per TimerOn settings)
     _avr_timer_cntcurr--;             // Count down to 0 rather than up to TOP
     if (_avr_timer_cntcurr == 0) {     // results in a more efficient compare
         TimerISR();                 // Call the ISR that the user uses
         _avr_timer_cntcurr = _avr_timer_M;
     }
 }

 #define button (~PINA & 0x04)

 enum STATES_A { STARTA, LED1, LED2, LED3 } stateA;
 enum STATES_B { STARTB, LED4, OFFB } stateB;
 enum STATES_C { STARTC, SOUND, OFFC } stateC;
 unsigned char outputA = 0x00;
 unsigned char outputB = 0x00;
 unsigned char pulse;

 void tickA(){
   switch(stateA){
     case STARTA:
     stateA = LED1;
     break;

     case LED1:
     stateA = LED2;
     break;

     case LED2:
     stateA = LED3;
     break;

     case LED3:
     stateA = LED1;
     break;

   }

   switch(stateA){
     case STARTA:
     break;

     case LED1:
     outputA = 0x01;
     break;

     case LED2:
     outputA = 0x02;
     break;

     case LED3:
     outputA = 0x04;
     break;

   }

 }

 void tickB(){
   switch(stateB){
     case STARTB:
     stateB = OFFB;
     break;

     case LED4:
     stateB = OFFB;
     break;

     case OFFB:
     stateB = LED4;
     break;

   }

   switch(stateB){
     case STARTB:
     outputB = 0x00;
     break;

     case LED4:
     outputB = 0x08;
     break;

     case OFFB:
     outputB = 0x00;
     break;

   }

 }

 void tickC(){
   switch(stateC){
     case STARTC:
     stateC = OFFC;
     pulse = 0x00;
     break;

     case OFFC:
     if(button){
       stateC = SOUND;
     }
     else{
       stateC = OFFC;
     }
     break;

     case SOUND:
     if(button && (pulse < 2)){
       stateC = SOUND;
     }
     else{
       //pulse++;
       stateC = OFFC;
     }
     break;

   }

   switch(stateC){
     case STARTC:
     //PORTB = 0x00;
     break;

     case OFFC:
     pulse = 0x00;
     PORTB = 0x00 | outputB | outputA;
     break;

     case SOUND:
     pulse++;
     PORTB = 0x10 | outputB | outputA;
     break;

   }

 }


 int main(void){
     /* Insert DDR and PORT initializations */
     DDRA = 0x00;  PORTA = 0xFF;
     DDRB = 0xFF;  PORTB = 0x00;
     unsigned long THREE_TIMER = 300;
     unsigned long BLINK_TIMER = 1000;
     unsigned long SOUND_TIMER = 2;
     unsigned long SysPeriod = 1;
     TimerSet(SysPeriod); //set timer here
     TimerOn(); //turn on timer

     stateA = STARTA; //change to START state
     stateB = STARTB;
     stateC = STARTC;

     /* Insert your solution below */
     while(1){
      if(THREE_TIMER >= 300){
      tickA();
      THREE_TIMER = 0;
      }
      if(BLINK_TIMER >= 1000){
      tickB();
      BLINK_TIMER = 0;
      }
      if(SOUND_TIMER >= 2){
      tickC();
      SOUND_TIMER = 0;
      }

      while(!TimerFlag) { }
      TimerFlag = 0;
      THREE_TIMER += SysPeriod;
      BLINK_TIMER += SysPeriod;
      SOUND_TIMER += SysPeriod;
    }
    return 1;
}
