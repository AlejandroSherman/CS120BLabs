/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 #include <avr/io.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif


 void set_PWM(double frequency) {
   static double current_frequency;
   if (frequency != current_frequency) {
     if (!frequency) { TCCR3B &= 0x08; }
     else { TCCR3B |= 0x03; }
     if (frequency < 0.954) { OCR3A = 0xFFFF; }
     else if (frequency > 31250) { OCR3A = 0x0000; }
     else { OCR3A = (short) (8000000 / (128 * frequency)) - 1; }
     TCNT3 = 0;
     current_frequency = frequency;
   }
 }

 void PWM_on() {
   TCCR3A = (1 << COM3A0);
   TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
   set_PWM(0);
 }

 void PWM_off() {
   TCCR3A = 0x00;
   TCCR3B = 0x00;
 }

 #define button (~PINA & 0x07)
 enum STATES { INIT, WAIT, SETC4, SETD4, SETE4 } state;

 void tick() {
     switch(state) {
         case INIT:
         state = WAIT;
         break;

         case WAIT:
         if (button == 0x01){
           state = SETC4;
         }
         else if(button == 0x02){
           state = SETD4;
         }
         else if(button == 0x04){
           state = SETE4;
         }
         else {
           state = WAIT;
         }
         break;

         case SETC4:
         if (button == 0x01) {
             state = SETC4;
         }
         else {
             state = WAIT;
         }
         break;


         case SETD4:
         if (button == 0x02) {
             state = SETD4;
         }
         else {
             state = WAIT;
         }
         break;


         case SETE4:
         if (button == 0x04) {
             state = SETE4;
         }
         else {
             state = WAIT;
         }
         break;


     }
     switch(state) {
         case INIT:
         break;

         case WAIT:
         set_PWM(0);
         break;

         case SETC4:
         set_PWM(261.63); //261.63
         break;

         case SETD4:
         set_PWM(293.66);
         break;

         case SETE4:
         set_PWM(329.63);
         break;
     }
 }

 int main(void) {
     DDRA = 0x00; PORTA = 0xFF;
     DDRB = 0xFF; PORTB = 0x00;
     PWM_on();
     state = INIT;
     while(1) {
         tick();
     }
   return 1;
 }
