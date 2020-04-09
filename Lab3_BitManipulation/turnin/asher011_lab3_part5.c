/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #3  Exercise #5
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
     DDRD = 0x00; PORTD = 0x00;
 	   DDRB = 0xFE;	PORTB = 0x00; //sets last bit to be input
    /*Insert your solution below*/
     unsigned short weight = 0;

    while (1) {
    weight = (PIND << 1);
    weight = (weight | (PINB && 0xFE));

    if(weight >= 70){
			PORTB = 0x02;
		}
		else if(weight > 5){
			PORTB = 0x04;
		}
		else{
			PORTB = 0x00;
		}


 }
    return 1;

}
