/*	Author: asher011
 *  Partner(s) Name:
 *	Lab Section: 23
 *	Assignment: Lab #5  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

 #include <avr/io.h>
 #ifdef _SIMULATE_
 #include "simAVRHeader.h"
 #endif

 enum STATES{ START, INIT, WAIT1, SET1, WAIT2, SET2, WAIT3, SET3, WAIT4, SET4, WAIT5, SET5, WAIT6, SET6, WAIT7, SET7, WAIT8, SET8, WAIT9, SET9, WAIT10, SET10, WAIT11, SET11, WAIT12, SET12, WAIT13, SET13, WAIT14, SET14, WAIT15 } state;

 unsigned char input = 0x00;

 void tick() {
  input = (~PINA & 0x01);

  switch(state) { //transitions
    case START:
    state = INIT;
    break;
    case INIT:
    if (input) {
      state = WAIT1;
    } else {
      state = INIT;
    }
    break;

    case WAIT1:
    if (!input) {
      state = SET1;
    } else {
      state = WAIT1;
    }
    break;


    case SET1:
    if (input) {
      state = WAIT2;
    } else {
      state = SET1;
    }
    break;


    case WAIT2:
    if (!input) {
      state = SET2;
    } else {
      state = WAIT2;
    }
    break;


    case SET2:
    if (input) {
      state = WAIT3;
    } else {
      state = SET2;
    }
    break;


    case WAIT3:
    if (!input) {
      state = SET3;
    } else {
      state = WAIT3;
    }
    break;


    case SET3:
    if (input) {
      state = WAIT4;
    } else {
      state = SET3;
    }
    break;


    case WAIT4:
    if (!input) {
      state = SET4;
    } else {
      state = WAIT4;
    }
    break;


    case SET4:
    if (input) {
      state = WAIT5;
    } else {
      state = SET4;
    }
    break;


    case WAIT5:
    if (!input) {
      state = SET5;
    } else {
      state = WAIT5;
    }
    break;


    case SET5:
    if (input) {
    state = WAIT6;
  } else {
    state = SET5;
  }
    break;


    case WAIT6:
    if (!input) {
    state = SET6;
  } else {
    state = WAIT6;
  }
    break;



	case SET6:
	if (input) {
	state = WAIT7;
} else {
	state = SET6;
}
	break;


	case WAIT7:
	if (!input) {
	state = SET7;
  } else {
	state = WAIT7;
  }
	break;


case SET7:
 if (input) {
 state = WAIT9;
 } else {
 state = SET7;
 }
 break;

 case WAIT8:
 if (!input) {
	 state = SET8;
 } else {
	 state = WAIT8;
 }
 break;


 case SET8:
 if (input) {
	 state = WAIT9;
 } else {
	 state = SET8;
 }
 break;


 case WAIT9:
 if (!input) {
	 state = SET9;
 } else {
	 state = WAIT9;
 }
 break;


 case SET9:
 if (input) {
	 state = WAIT10;
 } else {
	 state = SET9;
 }
 break;


 case WAIT10:
 if (!input) {
	 state = SET10;
 } else {
	 state = WAIT10;
 }
 break;


 case SET10:
 if (input) {
	 state = WAIT11;
 } else {
	 state = SET10;
 }
 break;


 case WAIT11:
 if (!input) {
	 state = SET11;
 } else {
	 state = WAIT11;
 }
 break;


 case SET11:
 if (input) {
	 state = WAIT12;
 } else {
	 state = SET11;
 }
 break;


 case WAIT12:
 if (!input) {
	 state = SET12;
 } else {
	 state = WAIT12;
 }
 break;


 case SET12:
 if (input) {
 state = WAIT13;
} else {
 state = SET12;
}
 break;


 case WAIT13:
 if (!input) {
 state = SET13;
} else {
 state = WAIT13;
}
 break;



case SET13:
if (input) {
state = WAIT14;
} else {
state = SET13;
}
break;


case WAIT14:
if (!input) {
state = SET14;
} else {
state = WAIT14;
}
break;


case SET14:
if (input) {
state = WAIT15;
} else {
state = SET14;
}
break;


	case WAIT15:
	if (!input) {
	state = INIT;
  } else {
	state = WAIT15;
  }
	break;
  }


  switch (state) { //actions
    case START:
    break;

    case INIT:
    //PORTC = 0x00;
		PORTB = 0x00;
    break;


    case WAIT1:
      break;


    case SET1:
    //PORTC = 0x02;
    PORTB = 0x02;
      break;


    case WAIT2:
    break;


    case SET2:
    //PORTC = 0x05;
    PORTB = 0x05;
    break;


    case WAIT3:
    break;


    case SET3:
    //PORTC = 0x0A;
		PORTB = 0x0A;
    break;


    case WAIT4:
    break;


    case SET4:
    //PORTC = 0x15;
    PORTB = 0x15;
    break;


		case WAIT5:
    break;


    case SET5:
    //PORTC = 0x2A;
    PORTB = 0x2A;
    break;

		case WAIT6:
    break;


    case SET6:
    //PORTC = 0x55;
    PORTB = 0x55;
    break;

		case WAIT7:
    break;


    case SET7:
    //PORTC = 0x00;
    PORTB = 0x00;
    break;

		case WAIT8:
      break;


    case SET8:
    //PORTC = 0x00;
    PORTB = 0x00;
      break;


    case WAIT9:
    break;


    case SET9:
    //PORTC = 0x20;
    PORTB = 0x20;
    break;


    case WAIT10:
    break;


    case SET10:
    //PORTC = 0x50;
		PORTB = 0x50;
    break;


    case WAIT11:
    break;


    case SET11:
    //PORTC = 0x28;
    PORTB = 0x28;
    break;


		case WAIT12:
    break;


    case SET12:
    //PORTC = 0x54;
    PORTB = 0x54;
    break;

		case WAIT13:
    break;


    case SET13:
    //PORTC = 0x2A;
    PORTB = 0x2A;
    break;

		case WAIT14:
    break;


    case SET14:
    //PORTC = 0x55;
    PORTB = 0x55;
    break;

		case WAIT15:
    break;

  }
 }

 int main(void) {
    /* Insert DDR and PORT initializations */
		DDRA = 0x00; PORTA = 0xFF;
		//DDRC = 0xFF; PORTC = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
    while (1) {
      tick();
    }

    return 1;
 }
