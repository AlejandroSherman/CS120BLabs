/*	Author: asher011
 *  Partner(s) Name: N/A
 *	Lab Section: 23
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;  PORTA = 0xFF;
    DDRB = 0x00;  PORTB = 0xFF;
    DDRC = 0x00; PORTC = 0xFF;
    DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
    unsigned char tmpA, tmpB, tmpC, tmpD = 0x00;
    unsigned char allWeight = 0x00;
    while (1) {
            PORTD = 0x00;
            tmpA = PINA;
            tmpB = PINB;
            tmpC = PINC;
            tmpD = 0x00;

            if ((tmpA + tmpB + tmpC) > 140){
            tmpD = tmpD | 0x01;
            }
            if ((~(tmpA - tmpC)+1) > 80){
            tmpD = tmpD | 0x02;
            }
            
           
            allWeight = tmpA + tmpB + tmpC;
            allWeight = allWeight & 0xFC;

            tmpD = allWeight | tmpD;

            PORTD = tmpD;
     }  
    return 0;
}
