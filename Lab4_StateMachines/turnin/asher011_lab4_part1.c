/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #1
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

enum States { START, INIT, WAIT1, INVERSE_LIGHTS, WAIT2 } state;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        break;

     case INIT:
        if (!((PINA && 0x01) == 1)) {
           state = INIT;
        }
        else if ((PINA && 0x01) == 1) {
           state = WAIT1;
        }
        break;

     case WAIT1:
        if ((PINA && 0x01) == 1) {
           state = WAIT1;
        }
        else if (!((PINA && 0x01) == 1)) {
           state = INVERSE_LIGHTS;
        }
        break;

      case INVERSE_LIGHTS:
        if (!((PINA && 0x01) == 1)) {
          state = INVERSE_LIGHTS;
        }
        else if ((PINA && 0x01) == 1) {
          state = WAIT2;
        }
        break;

      case WAIT2:
        if ((PINA && 0x01) == 1) {
          state = WAIT2;
        }
        else if (!((PINA && 0x01) == 1)) {
          state = INIT;
        }
        break;

     default:
        break;
  } // Transitions

  switch(state) {   // State actions
     case INIT:
         PORTB = 0x01;
        break;

     case WAIT1:
        break;

      case INVERSE_LIGHTS:
          PORTB = 0x02;
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
    DDRB = 0xFF; PORTB = 0x00;
    state = START;
    /* Insert your solution below */
    while (1) {
     Tick();
    }
    return 1;
}
