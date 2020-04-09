/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(char port, char bit_position) {
	return ( (port >> bit_position) & 0x01 );
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRB = 0x00; PORTB = 0xFF; //input
    DDRC = 0xFF; PORTC = 0x00; //output
    /* Insert your solution below */
    unsigned char tmpA, tmpB = 0x00;
    unsigned char count = 0x00;
    unsigned char pos = 0x00;
    while (1) {
    tmpA = PINA;
    tmpB = PINB;
    for(pos = 0x00; pos < 8; pos++){
    count += GetBit(tmpA, pos);
    count += GetBit(tmpB, pos);
    }
    PORTC = count;
    count = 0x00;
    }
    return 1;
}
