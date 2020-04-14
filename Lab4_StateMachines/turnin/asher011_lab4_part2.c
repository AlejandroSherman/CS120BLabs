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

enum STATES { START, INIT, INCREMENT, RESET, DECREMENT } state;
	unsigned char count = 0x00;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        break;

     case INIT:
        if (PINA == 0x00) {
           state = RESET;
        }
        else if (PINA == 0x01) {
           state = INCREMENT;
        }
        else if (PINA == 0x02) {
           state = DECREMENT;
        }
        else{
          state = INIT;
        }
        break;

     case INCREMENT:
           state = INIT;
        break;

      case RESET:
           state = INIT;
        break;

      case DECREMENT:
          state = INIT;
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
    count = 7;
    /* Insert your solution below */
    while (1) {
     Tick();
     PORTC = count;
    }
    return 1;
}
