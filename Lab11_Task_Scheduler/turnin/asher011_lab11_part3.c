/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
 #include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "scheduler.h"
#include "keypad.h"
#include "io.c"
#endif

enum STATES { STATE_IN, DISPLAY_DATA };


unsigned char keyLED = 0x00;
unsigned char store = 0x00;

int tick1(int state) {
 unsigned char key_in;
 key_in = GetKeypadKey();
 switch(state) {
     case STATE_IN:
     switch(key_in) {
                   case '\0':
                   //keyLED = 0x1F;
                   //store = keyLED + '0';
                   break;
                   case '1':
                   keyLED = 0x01;
                   store = keyLED + '0';
                   break;
                   case '2':
                   keyLED = 0x02;
                   store = keyLED + '0';
                   break;
                   case '3':
                   keyLED = 0x03;
                   store = keyLED + '0';
                   break;
                   case '4':
                   keyLED = 0x04;
                   store = keyLED + '0';
                   break;
                   case '5':
                   keyLED = 0x05;
                   store = keyLED + '0';
                   break;
                   case '6':
                   keyLED = 0x06;
                   store = keyLED + '0';
                   break;
                   case '7':
                   keyLED = 0x07;
                   store = keyLED + '0';
                   break;
                   case '8':
                   keyLED = 0x08;
                   store = keyLED + '0';
                   break;
                   case '9':
                   keyLED = 0x09;
                   store = keyLED + '0';
                   break;
                   case 'A':
                   keyLED = 0x0A;
                   store = keyLED + 0x37;
                   break;
                   case 'B':
                   keyLED = 0x0B;
                   store = keyLED + 0x37;
                   break;
                   case 'C':
                   keyLED = 0x0C;
                   store = keyLED + 0x37;
                   break;
                   case 'D':
                   keyLED = 0x0D;
                   store = keyLED + 0x37;
                   break;
                   case '*':
                   keyLED = 0x0E;
                   store = keyLED + 0x1C;
                   break;
                   case '0':
                   keyLED = 0x00;
                   store = keyLED + '0';
                   break;
                   case '#':
                   keyLED = 0x0F;
                   store = keyLED + 0x14;
                   break;
                   default:
                   keyLED = 0x1B;
                   break;
           }
           key_in = GetKeypadKey();

           if (key_in != '\0') {
             state = STATE_IN;
           }
           else {
             state = DISPLAY_DATA;
           }

   //state = DISPLAY_DATA;
   break;

   case DISPLAY_DATA:
   PORTB = keyLED;
   LCD_Cursor(1);
   if(store != 0){
    LCD_WriteData(store);
   }
   //break;

   key_in = GetKeypadKey();

   if (key_in != '\0') {
     state = STATE_IN;
   }
   else {
     state = DISPLAY_DATA;
   }
   break;
 }

 return state;
}

int main(void) {
   /* Insert DDR and PORT initializations */
   DDRA = 0xF0; PORTA = 0x0F;
   DDRB = 0xFF; PORTB = 0x00;
   DDRC = 0xFF; PORTC = 0x00;
   DDRD = 0xFF; PORTD = 0x00;
   // unsigned long int
   static task task1;
   task *tasks[] = { &task1};
   const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

      // Task 1
      task1.state = 0;//Task initial state.
      task1.period = 15;//Task Period.
      task1.elapsedTime = task1.period;//Task current elapsed time.
      task1.TickFct = &tick1;//Function pointer for the tick.

      TimerSet(5);
      TimerOn();
      LCD_init();
      LCD_ClearScreen();

    unsigned short i; // Scheduler for-loop iterator
      while(1) {
          for ( i = 0; i < numTasks; i++ ) {
              if ( tasks[i]->elapsedTime == tasks[i]->period ) {
                  tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
                  tasks[i]->elapsedTime = 0;
              }
              tasks[i]->elapsedTime += 1;
          }
          while(!TimerFlag);
          TimerFlag = 0;
      }
   return 0;
}
