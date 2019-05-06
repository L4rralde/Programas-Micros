#include<htc.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

void pause( unsigned short msvalue );		//Establish pause routine function
void msecbase( void );						//Establish millisecond base function

void main(){
    ANSEL =	0x00;
    ANSELH= 0x00;
    TRISC = 0x00;			//All PortC I/O outputs
    TRISB = 0x00;
    PORTC = 0x00;			//Clear PortC port
    PORTB = 0x00;

    while(1){
            RC0 = 1;         	// Turn on RC0 LED 
            RC1 = 0;			// Turn off RC1 LED
            pause(500);       	// Delay for .5 seconds

            RC0 = 0;       		// Turn off RC0 LED 
            RC1 = 1;			// Turn on RC1 LED
            pause(500);       	// Delay for .5 seconds
    }	
}


//*******************************************************
//pause - multiple millisecond delay routine
//*******************************************************

void pause( unsigned short msvalue ){
	for (unsigned short x=0; x<=msvalue; x++) msecbase();				//Jump to millisec delay routine
}


/********************************************************
* msecbase - 1 msec pause routine						*
* The Internal oscillator is set to 4 Mhz and the		*
* internal instruction clock is 1/4 of the oscillator.	*
* This makes the internal instruction clock 1 Mhz or	*
* 1 usec per clock pulse.								*
* Using the 1:4 prescaler on the clock input to Timer0	* 
* slows the Timer0 count increment to 1 count/4 usec.	*
* Therefore 250 counts of the Timer0 would make a one	*
* millisecond delay (250 * 4 usec). But there are other	*
* instructions in the delay loop so using the MPLAB 	*
* stopwatch we find that we need Timer0 to overflow at 	*
* 243 clock ticks. Preset Timer0 to 13 (0D hex) to make	*
* Timer0 overflow at 243 clock ticks (256-13 = 243).	*
* This results in a 1.001 millisecond delay which is 	*
* close enough.											*
*********************************************************/

void msecbase(void){
    //La siguiente línea fue la única que se cambió. Antes estaba como OPTION. 
    //En el PIC16F887 se llama OPTION_REG.
	OPTION_REG = 0b00000001;		//Set prescaler to TMRO 1:4
	TMR0 = 0x0D;					//Preset TMRO to overflow on 250 counts
	while(!T0IF);				//Stay until TMRO overflow flag equals 1
	T0IF = 0;					//Clear the TMR0 overflow flag
}
