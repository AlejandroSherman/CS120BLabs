/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #3  Exercise #3
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

     /*Insert DDR and PORT initializations*/
    DDRA = 0x00; PORTA = 0xFF;//input
    DDRC = 0xFF; PORTC = 0x00;//output
    /*Insert your solution below*/
    unsigned char fuelLev = 0x00;
    unsigned char tmpA,tmpB,tmpC = 0x00;

    while (1) {

    tmpA = PINA;
    tmpA = ((tmpA & 0x10) >> 4) && 0x01;
    tmpB = PINA;
    tmpB = ((tmpB & 0x20) >> 5) && 0x01;
    tmpC = PINA;
    tmpC = ((tmpC & 0x40) >> 6) && 0x01;

    fuelLev = PINA & 0x0F; // & 0x0F
    if ((fuelLev >= 0x01) && (fuelLev <= 0x02)) {
				PORTC = 0x60;
		}
    if ((fuelLev >= 0x03) && (fuelLev <= 0x04)) {
				PORTC = 0x70;
		}
    if ((fuelLev >= 0x05) && (fuelLev <= 0x06)) {
				PORTC = 0x38;
		}
    if ((fuelLev >= 0x07) && (fuelLev <= 0x09)) {
				PORTC = 0x3C;
		}
    if ((fuelLev >= 0x0A) && (fuelLev <= 0x0C)) {
				PORTC = 0x3E;
		}
    if ((fuelLev >= 0x0D) && (fuelLev <= 0x0F)) {
				PORTC = 0x3F;
		}

    if((tmpA==0x01) && (tmpB==0x01) && (tmpC==0x00) ){ 
      PORTC = PORTC | 0x80;
    }
 }
    return 1;

}
