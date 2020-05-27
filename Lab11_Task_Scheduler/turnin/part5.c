/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #5
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

 #define button1 (~PIND & 0x01)
 #define button2 (~PIND & 0x02)
 #define button3 (~PIND & 0x04)

 //unsigned char flag = 1;

 enum STATES { STATE_OUT, MOVEOBS, MOVEPLAYER, PAUSE, LETGO };

 //unsigned char LCDout = 0x00;
 unsigned char playerloc = 1;
 unsigned char obs1 = 0x0F + 0x14;
 unsigned char obs2 = 0x0F + 0x14;
 unsigned char obs1loc = 10;
 unsigned char obs2loc = 32;



 int tick1(int state) {
   switch(state) {
     case STATE_OUT:
       if(button1){
         state = LETGO;
       }
       else{
         if ((playerloc == obs1loc) || (playerloc == obs2loc)){
             LCD_ClearScreen();
             LCD_DisplayString(1, "You lose!             Try Again?");
             obs1loc = 10;
             obs2loc = 32;
             state = PAUSE;
         }
         else{
         state = MOVEOBS;
         }
       }
       break;

      case MOVEOBS:
       if(obs1loc == 16){
       LCD_Cursor(1);
       LCD_WriteData(0x20);
       LCD_Cursor(16);
       LCD_WriteData(obs1);
       obs1loc--;
       }

       else{
         LCD_Cursor(obs1loc+1);
         LCD_WriteData(0x20);
         LCD_Cursor(obs1loc);
         LCD_WriteData(obs1);
         obs1loc--;
       }

       if(obs1loc == 0){
         obs1loc = 16;
       }

       if(obs2loc == 32){
       LCD_Cursor(17);
       LCD_WriteData(0x20);
       LCD_Cursor(32);
       LCD_WriteData(obs2);
       obs2loc--;
       }
       else{
         LCD_Cursor(obs2loc+1);
         LCD_WriteData(0x20);
         LCD_Cursor(obs2loc);
         LCD_WriteData(obs2);
         obs2loc--;
       }

       if(obs2loc == 16){
         obs2loc = 32;
       }

       state = MOVEPLAYER;
       break;

       case MOVEPLAYER:
        LCD_Cursor(playerloc);
        if(button2){
          playerloc = 1;
        }
        if(button3){
          playerloc = 17;
        }
        state = STATE_OUT;
        break;

        case PAUSE:
         if(button1){
         LCD_ClearScreen();
         state = STATE_OUT;
        }
        else{
          state = PAUSE;
        }
         break;

         case LETGO:
          if(button1){
          state = LETGO;
         }
         else{
           state = PAUSE;
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
       DDRD = 0xF0; PORTD = 0x0F;

     // unsigned long int
     static task task1;
     task *tasks[] = { &task1};
     const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

        // Task 1
        task1.state = 0;//Task initial state.
        task1.period = 10;//Task Period.
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
