/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #4
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

enum STATES { START, INIT, COMB_1, WAIT, COMB_2, WAITC, COMB_3, WAITD, COMB_4, OPEN, COMB_1B, WAITB, COMB_2B, WAITCB, COMB_3B, WAITDB, COMB_4B} state;

void Tick()
{
  switch(state) {   // Transitions
     case START:  // Initial transition
        state = INIT;
        break;

     case INIT:
        if (PINA == 0x04) {
           state = COMB_1;
        }
        else if (PINA == 0x00) {
           state = INIT;
        }
        else if (PINA == 0x02) {
           state = INIT;
        }
        else {
          state = INIT;
        }
        break;

     case COMB_1:
     if (PINA == 0x04){
        state = COMB_1;
     }
     else if (PINA == 0x00) {
        state = WAIT;
     }
     else if (PINA == 0x02) {
        state = INIT;
     }
     else {
       state = INIT;
     }
        break;

     case WAIT:
        if (PINA == 0x00){
           state = WAIT;
        }
        else if (PINA == 0x04) {
           state = INIT;
        }
        else if (PINA == 0x01) {
           state = COMB_2;
        }
        else {
          state = INIT;
        }
        break;

        case COMB_2:
        if (PINA == 0x01){
           state = COMB_2;
        }
        else if (PINA == 0x00) {
           state = WAITC;
        }
        else if (PINA == 0x02) {
           state = INIT;
        }
        else {
          state = INIT;
        }
           break;

           case WAITC:
              if (PINA == 0x00){
                 state = WAITC;
              }
              else if (PINA == 0x04) {
                 state = INIT;
              }
              else if (PINA == 0x02) {
                 state = COMB_3;
              }
              else {
                state = INIT;
              }
              break;

              case COMB_3:
              if (PINA == 0x02){
                 state = COMB_3;
              }
              else if (PINA == 0x00) {
                 state = WAITD;
              }
              else if (PINA == 0x04) {
                 state = INIT;
              }
              else {
                state = INIT;
              }
                 break;


                 case WAITD:
                    if (PINA == 0x00){
                       state = WAITD;
                    }
                    else if (PINA == 0x04) {
                       state = INIT;
                    }
                    else if (PINA == 0x01) {
                       state = COMB_4;
                    }
                    else {
                      state = INIT;
                    }
                    break;

                    case COMB_4:
                    if (PINA == 0x01){
                       state = OPEN;
                    }
                    else if (PINA == 0x00) {
                       state = OPEN;
                    }
                    else if (PINA == 0x04) {
                       state = INIT;
                    }
                    else {
                      state = INIT;
                    }
                       break;


      case OPEN:
         if (PINA == 0x00){
            state = OPEN;
          }
          else if (PINA == 0x80) {
            state = INIT;
          }
          else if (PINA == 0x04) {
             state = COMB_1B;
          }
          else if (PINA == 0x02) {
             state = OPEN;
          }
          else{
            state = OPEN;
          }
          break;


          case COMB_1B:
          if (PINA == 0x04){
             state = COMB_1B;
          }
          else if (PINA == 0x00) {
             state = WAITB;
          }
          else if (PINA == 0x02) {
             state = OPEN;
          }
          else {
            state = OPEN;
          }
             break;

          case WAITB:
          if (PINA == 0x00){
             state = WAITB;
          }
          else if (PINA == 0x04) {
             state = OPEN;
          }
          else if (PINA == 0x01) {
             state = COMB_2B;
          }
          else {
            state = OPEN;
          }
             break;

             case COMB_2B:
             if (PINA == 0x01){
                state = COMB_2B;
             }
             else if (PINA == 0x00) {
                state = WAITCB;
             }
             else if (PINA == 0x02) {
                state = OPEN;
             }
             else {
               state = OPEN;
             }
                break;

                case WAITCB:
                if (PINA == 0x00){
                   state = WAITCB;
                }
                else if (PINA == 0x04) {
                   state = OPEN;
                }
                else if (PINA == 0x02) {
                   state = COMB_3B;
                }
                else {
                  state = OPEN;
                }
                   break;

                   case COMB_3B:
                   if (PINA == 0x02){
                      state = COMB_3B;
                   }
                   else if (PINA == 0x00) {
                      state = WAITDB;
                   }
                   else if (PINA == 0x04) {
                      state = OPEN;
                   }
                   else {
                     state = OPEN;
                   }
                      break;

                      case WAITDB:
                      if (PINA == 0x00){
                         state = WAITDB;
                      }
                      else if (PINA == 0x04) {
                         state = OPEN;
                      }
                      else if (PINA == 0x01) {
                         state = COMB_4B;
                      }
                      else {
                        state = OPEN;
                      }
                         break;

                         case COMB_4B:
                         if (PINA == 0x01){
                            state = INIT;
                         }
                         else if (PINA == 0x00) {
                            state = INIT;
                         }
                         else if (PINA == 0x04) {
                            state = OPEN;
                         }
                         else {
                           state = OPEN;
                         }
                            break;

     default:
        break;
  } // Transitions

  switch(state) {   // State actions
     case INIT:
       PORTB = 0;
        break;

     case COMB_1:
        break;

      case WAIT:
        break;

      case COMB_2:
         break;

         case OPEN:
           PORTB = 1;
            break;

            case COMB_1B:
               break;

             case WAITB:
               break;

             case COMB_2B:
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
