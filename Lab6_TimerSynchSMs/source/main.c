/*    Author: asher011
*  Partner(s) Name:
*    Lab Section: 023
*    Assignment: Lab #6 Exercise #2
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

enum STATES { START, LED_1, LED_2, LED_3, LED_4, WAIT, WAIT2, STOP } state;

//unsigned char output = 0x00;

void TimerOn() {
 TCCR1B = 0x0B;

 OCR1A = 125;

 TIMSK1 = 0x02;

 TCNT1 = 0;

 _avr_timer_cntcurr = _avr_timer_M;


 SREG |= 0x80;
}

void TimerOff() {
 TCCR1B = 0x00;
}

void TimerISR() {
 TimerFlag = 1;
}


// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
    _avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
    if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
        TimerISR(); // Call the ISR that the user uses
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}


void tick() {
  unsigned char button = (~PINA & 0x01);


 switch(state) {
   case START:
   state = LED_1;
   break;


   case LED_1:
   if(button){
    state = WAIT;
   }
   else{
   state = LED_2;
   }
   break;


   case LED_2:
   if(button){
    state = WAIT;
   }
   else{
   state = LED_3;
   }
   break;


   case LED_3:
   if(button){
    state = WAIT;
   }
   else{
   state = LED_4;
   }
   break;

   case LED_4:
   if(button){
    state = WAIT;
   }
   else{
   state = LED_1;
   }
   break;


   // case LED_5:
   // if(button){
   //  state = WAIT;
   // }
   // else{
   // state = LED_1;
   // }
   // break;

   case WAIT:
   if(button){
     state = WAIT;
   }
   else {
     state = STOP;
   }
   break;

   case STOP:
   if(button){
     state = WAIT2;
   }
   else {
     state = STOP;
   }
   break;

   case WAIT2:
   if(button){
     state = WAIT2;
   }
   else {
     state = LED_1;
   }
   break;
   }


 switch(state) {
   case START:
   break;


   case LED_1:
   PORTB = 0x01;
   break;


   case LED_2:
   PORTB = 0x02;
   break;


   case LED_3:
   PORTB = 0x04;
   break;

   case LED_4:
   PORTB = 0x02;
   break;


   // case LED_5:
   // PORTB = 0x01;
   // break;

   case WAIT:
   break;

   case WAIT2:
   break;

   case STOP:
   break;
 }
}


int main(void) {
   /* Insert DDR and PORT initializations */
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   TimerSet(30); //set timer here
   TimerOn(); //turn on timer
   state = START; //change to START state

   /* Insert your solution below */
   while (1) {
     tick();
     while (!TimerFlag);

     TimerFlag = 0;
     //PORTB = output;
   }

   return 1;
}
