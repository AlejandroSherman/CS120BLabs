/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 023
 *	Assignment: Lab #8  Exercise #4
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
 //DDRD = 0xFF; PORTD = 0x00;
 unsigned char output = 0x00;
 unsigned short MAX = 80;
 ADC_init();


 while(1){

 unsigned long x = ADC;


if (x >= MAX) {
  output = 0xFF;
}
else if (x >= 75) {
  output = 0x7F;
}
else if (x >= 70) {
  output = 0x5F;
}
else if (x >= 65) {
  output = 0x3F;
}
else if (x >= 60) {
  output = 0x1F;
}
else if (x >= 55) {
  output = 0x0F;
}
else if (x >= 50) {
  output = 0x07;
}
else if (x >= 45) {
  output = 0x03;
}
else if (x >= 40) {
  output = 0x01;
}
/*
else if (x >= 25) {
  output = 0x00;
}

else if (x >= 40) {
  output = 0x0F;
}
else if (x >= 30) {
  output = 0x07;
}
else if (x >= 20) {
  output = 0x03;
}
else {
  output = 0x01;
}
*/
  PORTB = output;
}


  return 1;
 }
