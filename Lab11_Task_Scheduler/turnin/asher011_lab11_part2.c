/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #2
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

 //unsigned char LCDout = 0x00;
 unsigned char offset = 1;
 unsigned char i;

 const unsigned char MESSAGE[72]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
 //const unsigned char MESSAGE[60]={' ',' ',' ',' ','C','S','1','2','0','B',' ','i','s',' ','L','e','g','e','n','d','.','.','.','w','a','i','t',' ','f','o','r',' ','i','t',' ','D','A','R','Y','!',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
 int tick1(int state) {
   switch(state) {
     case STATE_OUT:
     for (i = 1; i <= 16; i++) {//change to 16 to be one row //32 equala both rows
       LCD_Cursor(i);
       LCD_WriteData(MESSAGE[offset+i-2]);
       if (offset+i+1 == 72) {//60
         offset = 1;
       }
     }
     offset++;
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
