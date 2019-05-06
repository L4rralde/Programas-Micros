#include <htc.h>

void msecbase(void){
	OPTION_REG= 0b00000001;		//Set prescaler to TMRO 1:4
	TMR0 = 0x0D;			//Preset TMRO to overflow on 250 counts
	while(!T0IF);			//Stay until TMRO overflow flag equals 1
	T0IF = 0;			//Clear the TMR0 overflow flag
}
