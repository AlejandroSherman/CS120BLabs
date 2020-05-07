/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 023
 *	Assignment: Lab #8  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

 #include <avr/io.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif

 void ADC_init() {
 ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
 // ADEN: setting this bit enables analog-to-digital conversion.
 // ADSC: setting this bit starts the first conversion.
 // ADATE: setting this bit enables auto-triggering. Since we are
 //        in Free Running Mode, a new conversion will trigger whenever
 //        the previous conversion completes.
 }


 int main(void) {
 DDRA = 0x00; PORTA = 0xFF;
 DDRB = 0xFF; PORTB = 0x00;
 DDRD = 0xFF; PORTD = 0x00;
 ADC_init();

 while(1){
 unsigned short x = ADC;
 unsigned char bottom8 = (char)x;
 PORTB = bottom8;
 unsigned char top2 = (char)(x >> 8);
 PORTD = top2;
 }

    return 1;
 }
