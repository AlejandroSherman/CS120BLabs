/*    Author: asher011
*  Partner(s) Name:
*    Lab Section: 023
*    Assignment: Lab #7 Exercise #2
*    Exercise Description: [optional - include for your own benefit]
*
*    I acknowledge all content contained herein, excluding template or example
*    code, is my own original work.
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#endif

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

enum STATES { START, START2, LED_1, LED_2, LED_3, LED_4, WAIT, WAIT2, STOP, WIN } state;
unsigned char i = 0x00;
unsigned char score = 5;
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
   LCD_ClearScreen();
   LCD_WriteData(score + '0');
   state = LED_1;
   break;

   case START2:
   state = LED_1;
   break;

   case LED_1:
   if(button){
    if(score > 0){
      score--;
      LCD_ClearScreen();
      LCD_WriteData(score + '0');
    }
    state = WAIT;
   }
   else if ((!button) && (i <= 3)){
   state = LED_1;
   }
   else if ((!button) && (i > 3)){
   state = LED_2;
   i = 0;
   }
   break;


   case LED_2:
   if(button){
     if(score < 9){
       score++;
       LCD_ClearScreen();
       LCD_WriteData(score + '0');
     }
    state = WAIT;
   }
   else if ((!button) && (i <= 3)){
   state = LED_2;
   }
   else if ((!button) && (i > 3)){
   state = LED_3;
   i = 0;
   }
   break;


   case LED_3:
   if(button){
     if(score > 0){
       score--;
       LCD_ClearScreen();
       LCD_WriteData(score + '0');
     }
    state = WAIT;
   }
   else if ((!button) && (i <= 3)){
   state = LED_3;
   }
   else if ((!button) && (i > 3)){
   state = LED_4;
   i = 0;
   }
   break;

   case LED_4:
   if(button){
     if(score < 9){
       score++;
       LCD_ClearScreen();
       LCD_WriteData(score + '0');
     }
    state = WAIT;
   }
   else if ((!button) && (i <= 3)){
   state = LED_4;
   }
   else if ((!button) && (i > 3)){
   state = START2;
   i = 0;
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
   else if(score == 9){
     LCD_ClearScreen();
     LCD_DisplayString(1, "YOU WIN!!!");
     state = WIN;
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
     state = START2;
   }
   break;


   case WIN:
   if(button){
     score = 5;
     LCD_ClearScreen();
     LCD_WriteData(score + '0');
     state = WAIT2;
   }
   else {
     state = WIN;
   }
   break;
}
 switch(state) {
   case START:
   i = 0;
   break;

   case START2:
   i = 0;
   break;

   case LED_1:
   PORTB = 0x01;
   i++;
   break;


   case LED_2:
   PORTB = 0x02;
   i++;
   break;


   case LED_3:
   PORTB = 0x04;
   i++;
   break;

   case LED_4:
   PORTB = 0x02;
   i++;
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

   case WIN:
   break;
 }
}


int main(void) {
   /* Insert DDR and PORT initializations */
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   DDRC = 0xFF; PORTC = 0x00;
   DDRD = 0xFF; PORTD = 0x00;
   //unsigned char button2 = (~PINA & 0x01);

   TimerSet(10); //set timer here
   TimerOn(); //turn on timer
   LCD_init();
   LCD_Cursor(1);
   state = START; //change to START state
   score = 5;
   /* Insert your solution below */
   while (1) {
     tick();
    while (!TimerFlag);

    TimerFlag = 0;
    //PORTB = output;
    }

   return 1;
}
