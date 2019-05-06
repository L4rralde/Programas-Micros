#include <htc.h>
#include "pause.h"

#define SW1	 	RA3	

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

void main(){
    unsigned char state_led = 0; 	//Create 8 bit variable to store switch count
    ANSEL =	0x00;				// Intialize A/D ports off
    ANSELH= 0x00;
    TRISC = 0x00;			//All PortC I/O outputs
    TRISB = 0x00; 
    TRISA = 0xFF;			//All PortA I/O inputs
    PORTC = 0x00;			//Clear PortC port
    PORTB = 0x00; 
    
    while(1){
        if (SW1 == 0){					
            state_led++;		//  increment the LED state variable
            switch (state_led){
                case 1:					// STATE0: turn only the D0 LED on
                    RC0 = 1;
                    RC1 = 0;
                    RC2 = 0;
                    RC3 = 0;
                    break;
                case 2:					// STATE1: turn only the D1 LED on
                    RC0 = 0;
                    RC1 = 1;
                    RC2 = 0;
                    RC3 = 0;
                    break;
                case 3:					// STATE2: turn only the D2 LED on
                    RC0 = 0;
                    RC1 = 0;
                    RC2 = 1;
                    RC3 = 0;
                    break;
                case 4:					// STATE3: turn only the D3 LED on
                    RC0 = 0;
                    RC1 = 0;
                    RC2 = 0;
                    RC3 = 1;
                    break;
                default:				// If state_led > 3 reset switch count to zero
                    state_led = 0;		// All LEDs off	
                    RC0 = 0;
                    RC1 = 0;
                    RC2 = 0;
                    RC3 = 0;				
                    break;
            } //end switch
            while (!SW1);				// Hold here until switch is released
            pause (10);					// Delay 10 milliseconds and check again
            while (!SW1);				// For simple debounce of switch
        } //End If
    }	//End while
}	//end main