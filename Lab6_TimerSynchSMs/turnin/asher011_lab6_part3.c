/*    Author: asher011
*  Partner(s) Name:
*    Lab Section: 023
*    Assignment: Lab #6 Exercise #3
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

enum STATES { START, INIT, INCREMENT, WAIT1, RESET, DECREMENT, WAIT2} state;
	unsigned char count = 0x07;
  unsigned char value = 0x00;
  unsigned char i = 0x00;
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


void tick()
{
  value = ((~PINA) & 0x0F);
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        count = 7;
        break;

     case INIT:
        if (value == 0x03) {
           state = RESET;
        }
        else if (value == 0x01) {
           state = INCREMENT;
        }
        else if (value == 0x02) {
           state = DECREMENT;
        }
        break;

     case INCREMENT:
           state = WAIT1;
           // if (value == 0x01){
           //    state = INCREMENT;
           // }
           // else if (value == 0x00) {
           //    state = INIT;
           // }
           // else if (value == 0x03) {
           //    state = RESET;
           // }
        break;

     case WAIT1:
        if ((value == 0x01) && (i > 10)){
           state = INCREMENT;
        }
        else if ((value == 0x01) && (i <= 10)){
           state = WAIT1;
        }
        else if (value == 0x00) {
           state = INIT;
        }
        else if (value == 0x03) {
           state = RESET;
        }
        break;

      case RESET:
           state = INIT;
        break;

      case DECREMENT:
          state = WAIT2;
          // if (value == 0x02){
          //    state = DECREMENT;
          //  }
          //  else if (value == 0x00) {
          //    state = INIT;
          //  }
          //  else if (value == 0x03) {
          //     state = RESET;
          //  }
        break;

        case WAIT2:
          if ((value == 0x02) && (i > 10)){
           state = DECREMENT;
          }
          else if ((value == 0x02) && (i <= 10)){
            state = WAIT2;
          }
          else if (value == 0x00) {
            state = INIT;
          }
          else if (value == 0x03) {
             state = RESET;
          }
          break;

     default:
        break;
  } // Transitions

  switch(state) {   // State actions
     case INIT:
         i = 0;
        break;

     case INCREMENT:
        if(count < 9){
          count++;
        }
        i = 0;
        break;

      case DECREMENT:
        if(count > 0){
          count--;
        }
        i = 0;
        break;

      case RESET:
          count = 0;
         break;

      case WAIT1:
        i++;
        break;

      case WAIT2:
        i++;
         break;

     default:
        break;
   } // State actions
}


int main(void) {
   /* Insert DDR and PORT initializations */
   DDRA = 0x00; PORTA = 0xFF;
   DDRB = 0xFF; PORTB = 0x00;
   TimerSet(10); //set timer here
   TimerOn(); //turn on timer
   state = START; //change to START state
   count = 7;
   /* Insert your solution below */
   while (1) {
     tick();
     while (!TimerFlag);

     TimerFlag = 0;
     PORTB = count;
   }

   return 1;
}
