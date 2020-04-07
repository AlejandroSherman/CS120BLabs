/*	Author: asher011
 *  Partner(s) Name: N/A
 *	Lab Section: 23
 *	Assignment: Lab #2  Exercise #1
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
    DDRB = 0xFF;
    PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
            PORTB = 0x0F;
    }
    return 1;
}
