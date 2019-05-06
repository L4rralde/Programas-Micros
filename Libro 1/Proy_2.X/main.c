#include<htc.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

void main(){
    ANSEL =	0x00;				// Intialize A/D ports off
    ANSELH= 0x00;
    PORTC = 0x00;				//Clear PortC port
    TRISC = 0x00;				//All PortC I/O outputs

    unsigned int contador;
    while(1)					//loop forever
    {
        RC0 = 1;         		// Turn on RC0 LED 
        contador = 65535;		// Preset counter to 65535
        do{	
            contador -= 1;	// Decrement count by one
        }	
        while (contador > 0);		// Loop until counter = 0 for delay time
        //PORTC = 0b00000001;
        RC0 = 0;       			// Turn off RC0 LED 
        contador = 65535;		// Preset counter to 65535
        do{	
            contador -= 1;	// Decrement count by one
        }	
        while (contador > 0);		// Loop until counter = 0 for delay time
    }	
}	
