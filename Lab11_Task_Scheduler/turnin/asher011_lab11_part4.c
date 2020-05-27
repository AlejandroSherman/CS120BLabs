/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #4
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

enum STATES { STATE_OUT };

unsigned char curLoc = 1;
unsigned char keyLED = 0x00;

int tick1(int state) {
  unsigned char key_in;
  key_in = GetKeypadKey();
  switch(state) {
    case STATE_OUT:
    switch(key_in) {
                  case '\0':
                  keyLED = 0x1F;
                  //PORTB = keyLED;
                  break;
                  case '1':
                  keyLED = 0x01;
                  PORTB = keyLED;
                  while(key_in == '1'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '2':
                  keyLED = 0x02;
                  PORTB = keyLED;
                  while(key_in == '2'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '3':
                  keyLED = 0x03;
                  PORTB = keyLED;
                  while(key_in == '3'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '4':
                  keyLED = 0x04;
                  PORTB = keyLED;
                  while(key_in == '4'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '5':
                  keyLED = 0x05;
                  PORTB = keyLED;
                  while(key_in == '5'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '6':
                  keyLED = 0x06;
                  PORTB = keyLED;
                  while(key_in == '6'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '7':
                  keyLED = 0x07;
                  PORTB = keyLED;
                  while(key_in == '7'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '8':
                  keyLED = 0x08;
                  PORTB = keyLED;
                  while(key_in == '8'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '9':
                  keyLED = 0x09;
                  PORTB = keyLED;
                  while(key_in == '9'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case 'A':
                  keyLED = 0x0A;
                  PORTB = keyLED;
                  while(key_in == 'A'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x37);
                  curLoc++;
                  break;
                  case 'B':
                  keyLED = 0x0B;
                  PORTB = keyLED;
                  while(key_in == 'B'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x37);
                  curLoc++;
                  break;
                  case 'C':
                  keyLED = 0x0C;
                  PORTB = keyLED;
                  while(key_in == 'C'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x37);
                  curLoc++;
                  break;
                  case 'D':
                  keyLED = 0x0D;
                  PORTB = keyLED;
                  while(key_in == 'D'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x37);
                  curLoc++;
                  break;
                  case '*':
                  keyLED = 0x0E;
                  PORTB = keyLED;
                  while(key_in == '*'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x1C);
                  curLoc++;
                  break;
                  case '0':
                  keyLED = 0x00;
                  PORTB = keyLED;
                  while(key_in == '0'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + '0');
                  curLoc++;
                  break;
                  case '#':
                  keyLED = 0x0F;
                  PORTB = keyLED;
                  while(key_in == '#'){
                    key_in = GetKeypadKey();
                  }
                  LCD_Cursor(curLoc);
                  LCD_WriteData(keyLED + 0x14);
                  curLoc++;
                  break;
                  default:
                  keyLED = 0x1B;
                  break;
    }
    if(curLoc == 17){
      curLoc = 1;
    }
    state = STATE_OUT;
    PORTB = keyLED;
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
       task1.period = 20;//Task Period.
       task1.elapsedTime = task1.period;//Task current elapsed time.
       task1.TickFct = &tick1;//Function pointer for the tick.

       TimerSet(10);
       TimerOn();
       LCD_init();
       LCD_DisplayString(1,"Congratulations");

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
