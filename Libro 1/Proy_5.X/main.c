#include<htc.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

void main(){
    ANSEL =	0x00;			//Intialize A/D ports off    
    ANSELH= 0x00;
    TRISC = 0x00;			//All PortC I/O outputs
    TRISA = 0xFF;			//All PortA I/O inputs
    PORTC = 0x00;			//Clear PortC port
    
    while(1){
        if (RA3 == 1){
            RC0 = 1;         	// If SW1 not pressed, turn on RC0/DS1 LED 
        }
        else{
            RC0 = 0;			// If SW1 pressed, turn off RC1/DS2 LED
        }	
    }	//End while
}	//end main