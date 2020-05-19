/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 #include <avr/io.h>
 #include <avr/interrupt.h>
 //#include <timer.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif

 //#include <avr/interrupt.h>

 volatile unsigned char TimerFlag = 0;
 unsigned long _avr_timer_M = 1;
 unsigned long _avr_timer_cntcurr = 0;
 void TimerOn()
 {
     TCCR1B = 0x0B;
     OCR1A = 125;
     TIMSK1 = 0x02;
     TCNT1 = 0;
     _avr_timer_cntcurr = _avr_timer_M;
     SREG |= 0x80;
 }
 void TimerOff()
 {
     TCCR1B = 0x00;
 }
 void TimerISR()
 {
     TimerFlag = 1;
 }
 ISR(TIMER1_COMPA_vect)
 {
     _avr_timer_cntcurr--;
     if (_avr_timer_cntcurr == 0)
     {
         TimerISR();
         _avr_timer_cntcurr = _avr_timer_M;
     }
 }
 void TimerSet(unsigned long M)
 {
     _avr_timer_M = M;
     _avr_timer_cntcurr = _avr_timer_M;
 }

 void set_PWM(double frequency) {
     // Keeps track of the currently set frequency
     // Will only update the registers when the frequency
     // changes, plays music uninterrupted.
     static double current_frequency;
     if (frequency != current_frequency) {

         if (!frequency) TCCR3B &= 0x08; //stops timer/counter
         else TCCR3B |= 0x03; // resumes/continues timer/counter

         // prevents OCR3A from overflowing, using prescaler 64
         // 0.954 is smallest frequency that will not result in overflow
         if (frequency < 0.954) OCR3A = 0xFFFF;

         // prevents OCR3A from underflowing, using prescaler 64                    // 31250 is largest frequency that will not result in underflow
         else if (frequency > 31250) OCR3A = 0x0000;

         // set OCR3A based on desired frequency
         else OCR3A = (short)(8000000 / (128 * frequency)) - 1;

         TCNT3 = 0; // resets counter
         current_frequency = frequency;
     }
 }
 void PWM_on() {
     TCCR3A = (1 << COM3A0);
     // COM3A0: Toggle PB6 on compare match between counter and OCR3A
     TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
     // WGM32: When counter (TCNT3) matches OCR3A, reset counter
     // CS31 & CS30: Set a prescaler of 64
     set_PWM(0);
 }
 void PWM_off() {
     TCCR3A = 0x00;
     TCCR3B = 0x00;
 }


 #define button1 (~PINA & 0x01)
 #define button2 (~PINA & 0x02)
 #define button3 (~PINA & 0x04)


 enum STATES_A { STARTA, LED1, LED2, LED3 } stateA;
 enum STATES_B { STARTB, LED4, OFFB } stateB;
 enum STATES_C { STARTC, SOUND, OFFC } stateC;
 enum STATES_D { STARTD, WAIT, UP, HOLDUP, DOWN, HOLDDOWN } stateD;
 double NOTE[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
 unsigned char outputA = 0x00;
 unsigned char outputB = 0x00;
 unsigned char pulse;
 unsigned char pos = 0;

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
     if(button3){
       stateC = SOUND;
     }
     else{
       stateC = OFFC;
     }
     break;

     case SOUND:
     if(button3 && (pulse < 2)){
       stateC = SOUND;
     }
     else{
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
     set_PWM(0);
     PORTB = outputB | outputA;
     //PORTB = 0x00 | outputB | outputA;
     break;

     case SOUND:
     pulse++;
     set_PWM(NOTE[pos]);
     PORTB = outputB | outputA;
     //PORTB = 0x10 | outputB | outputA;
     break;

   }

 }

  void tickD(){
     switch(stateD){
        case STARTD:
        stateD = WAIT;
        break;

        case WAIT:
        if(button1){
        stateD = HOLDUP;
        }
        else if(button2) {
        stateD = HOLDDOWN;
        }
        else {
        stateD = WAIT;
        }
        break;

        case HOLDUP:
        if(button1){
        stateD = HOLDUP;
        }
        else{
        stateD = UP;
        }
        break;

        case UP:
        stateD = WAIT;
        break;

        case HOLDDOWN:
        if(button2){
        stateD = HOLDDOWN;
        }
        else{
        stateD = DOWN;
        }
        break;

        case DOWN:
        stateD = WAIT;
        break;

      }

      switch(stateD){
       case STARTD:
       pos = 0;
       break;

       case WAIT:
       break;

       case HOLDUP:
       break;

       case UP:
       if(pos < 7){
       pos++;
       }
       break;

       case HOLDDOWN:
       break;

       case DOWN:
       if(pos > 0){
       pos--;
       }
       break;
      }

  }


 int main(void){
     /* Insert DDR and PORT initializations */
     DDRA = 0x00;  PORTA = 0xFF;
     DDRB = 0xFF;  PORTB = 0x00;
     PWM_on();
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
      tickD();

      while(!TimerFlag) { }
      TimerFlag = 0;
      THREE_TIMER += SysPeriod;
      BLINK_TIMER += SysPeriod;
      SOUND_TIMER += SysPeriod;
    }
    return 1;
}
