/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 023
 *	Assignment: Lab #9  Exercise #2
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
 double NOTE[8] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
 enum STATES { INIT, OFF, ON, PRESSON, PRESSOFF, PLAY, UP, WAITUP, DOWN, WAITDOWN } state;
 unsigned char i;

 void tick() {
     switch(state) {
         case INIT:
         state = OFF;
         break;

         case OFF:
         if (button == 0x01) {
             state = PRESSON;
         }
         else {
             state = OFF;
         }
         break;

         case ON:
         state = PLAY;
         break;

         case PRESSON:
         if (button == 0x01) {
             state = PRESSON;
         }
         else {
             state = ON;
         }
         break;

         case PRESSOFF:
         if (button == 0x01) {
             state = PRESSOFF;
         }
         else {
             state = OFF;
         }
         break;

         case PLAY:
             if(button == 0x01){
               state = PRESSOFF;
             }
             else if (button == 0x02){
               state = WAITUP;
             }
             else if (button == 0x04){
               state = WAITDOWN;
             }
             else {
               state = PLAY;
             }
         break;

         case UP:
         state = PLAY;
         break;

         case WAITUP:
         if (button == 0x02) {
             state = WAITUP;
         }
         else {
             state = UP;
         }
         break;

         case DOWN:
         state = PLAY;
         break;

         case WAITDOWN:
         if (button == 0x04) {
             state = WAITDOWN;
         }
         else {
             state = DOWN;
         }
         break;
     }

     switch(state) {
         case INIT:
         break;

         case OFF:
         PWM_off();
         break;

         case ON:
         break;

         case PRESSON:
         PWM_on();
         i = 0;
         break;

         case PRESSOFF:
         break;

         case PLAY:
         set_PWM(NOTE[i]);
         break;

         case UP:
         if (i < 7) {
             i++;
         }
         break;

         case WAITUP:
         break;

         case DOWN:
         if (i > 0) {
             i--;
         }
         break;

         case WAITDOWN:
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
 }
