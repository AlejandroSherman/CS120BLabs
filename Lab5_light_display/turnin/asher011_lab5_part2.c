/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "RIMS.h"
#endif

enum STATES { START, INIT, INCREMENT, WAIT1, RESET, DECREMENT, WAIT2} state;
	unsigned char count = 0x00;
  unsigned char value = 0x00;

void Tick()
{
  value = ((~PINA) & 0x0F);
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        count = 0;
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
        break;

     case WAIT1:
        if (value == 0x01){
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
        break;

      case WAIT2:
         if (value == 0x02){
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
        break;

     case INCREMENT:
        if(count < 9){
          count++;
        }
        break;

      case DECREMENT:
        if(count > 0){
          count--;
        }
        break;

      case RESET:
          count = 0;
         break;

      case WAIT1:
        break;

      case WAIT2:
         break;

     default:
        break;
   } // State actions
}


int main(void) {
    /* Insert DDR and PORT initializations */
    //enum States { START, INIT, WAIT1, INVERSE_LIGHTS, WAIT2 } state;
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    state = START;
    count = 0;
    /* Insert your solution below */
    while (1) {
     Tick();
     PORTC = count;
    }
    return 1;
}
