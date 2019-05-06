#include<htc.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

unsigned short delay=500;			//Initialize on/off delay value to 500 msec
void Pause( unsigned short msvalue );		//Establish pause routine function
void msecbase( void );				//Establish millisecond base function

void main(){
    ANSEL =	0x00;				// Intialize A/D ports off
    ANSELH= 0x00;
    TRISC = 0x00;			//All PortC I/O outputs
    TRISB = 0x00;
    PORTC = 0x00;			//Clear PortC port
    PORTB = 0x00; 
    
    while(1){
        for(int x=1; x<9; x*=2){
            PORTC = x;         		// Turn on next LED 
            Pause(delay);       	// Delay for .5 seconds
        }	// End For
    }	//End while
}	//end main


//*******************************************************
//pause - multiple millisecond delay routine
//*******************************************************

void Pause( unsigned short msvalue ){
	for (unsigned short x=0; x<=msvalue; x++) msecbase();				//Jump to millisec delay routine
}


//*******************************************************
//msecbase - 1 msec pause routine
//*******************************************************

void msecbase(void)
{
	OPTION_REG = 0b00000001;		//Set prescaler to TMRO 1:4
	TMR0 = 0x0D;			//Preset TMRO to overflow on 250 counts
	while(!T0IF);			//Stay until TMRO overflow flag equals 1
	T0IF = 0;			//Clear the TMR0 overflow flag
}
