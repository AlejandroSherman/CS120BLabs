/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #3
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

enum STATES { START, INIT, COMB_1, WAIT, COMB_2, UNLOCK} state;
unsigned char tmpB;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        break;

     case INIT:
         if((PINA) == 0x01){
             state = COMB_1;
         }
         else{
             state = INIT;
         }
        break;

     case COMB_1:
        if((PINA) == 0x01){
          state = COMB_1;
        }
        else if((PINA) == 0x00){
          state = WAIT;
        }
        else{
          state = INIT;
        }
        break;

      case WAIT:
        if ((PINA) == 0x00){
          state = WAIT;
        }
        else if((PINA) == 0x02){
          state = COMB_2;
        }
        else {
          state = INIT;
        }
        break;

      case COMB_2:
        if ((PINA) == 0x02){
            state = COMB_2;
        }
        else if ((PINA) == 0x00){
            state = UNLOCK;
        }
        else{
            state = INIT;
        }
        break;

        case UNLOCK:
          if ((PINA) == 0x80){
              state = INIT;
          }
          else if ((PINA) == 0x00){
              state = UNLOCK;
          }
          break;


    // default:
    //    break;
  } // Transitions

  switch(state) {   // State actions
       case INIT:
           tmpB = 0x00;
           break;

      case START:
            break;

       case COMB_1:
           break;

       case WAIT:
           break;

       case COMB_2:
           break;

       case UNLOCK:
           tmpB = 0x01;
           break;

    // default:
    //    break;
   } // State actions
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA= 0xFF; PORTA=0x00;
    DDRB= 0x00; PORTB = 0xFF;
    state = START;
    /* Insert your solution below */
    while (1) {
     Tick();
     PORTB = tmpB;
    }
    return 1;
}
