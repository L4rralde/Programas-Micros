#define _LEGACY_HEADERS //Added for compiler versions 9.81+
#include <pic.h>

__CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT & UNPROTECT & BORDIS & IESODIS & FCMDIS);

#define DS1_on 0b00000001;			//Create nickname to light DS1 LED
#define DS2_on 0b00000011;			//Create nickname to light DS1,2 LED
#define DS3_on 0b00000111;			//Create nickname to light DS1,2,3 LED
#define DS4_on 0b00001111;			//Create nickname to light DS1,2,3,4 LED

int advalue = 0;					//Create A/D storage value and clear it

void main(){
    //Se cambiaron las líneas de ADCON0 y ADCON1
    ANSEL = 0x01;				//A/D module on
    ANSELH= 0x00;
    TRISA = 0xFF;			//All PortA I/O inputs
    TRISC = 0x00; 				//All PortC is output
    ADCON0 = 0b11000000;	//AtoD on, Left justified, Channel AN0/RA0 selected
    ADCON1 = 0x00;	//Internal RC clock for A/D conversion
    PORTC = 0x00;				//Clear PortC

    while(1){
        ADON=1; 
        NOP();
        NOP();
        NOP();
        NOP();
        GODONE = 1;	//Start A/D process
        while (GODONE)	//wait for A/D to finish
 
        advalue = ADRESH;		//Store A/D result in variable ADVALUE

        if (advalue >30) PORTC = DS1_on;		//Less than 60, light DS1 LED
        //RC3 = 1;
        
        if (advalue >90) PORTC = DS2_on;		//Less than 120, light DS1,2 LEDs
        //RC2 = 1;
        
        if (advalue >150) PORTC = DS3_on;		//Less than 180, light DS1,2,3 LEDs
        //RC1 = 1;
        
        if (advalue > 210) PORTC = DS4_on;		//Less than 240, light DS1,2,3,4 LEDs
        //RC0 = 1;
        
        if (advalue <= 30) PORTC = 0;			//Set all LEDs off
     
    }	//End While
}	//End Main
