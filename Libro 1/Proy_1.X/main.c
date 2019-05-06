#include<htc.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

void main(){
    ANSEL =	0x00;			//Puertos AD deshabilitados
    ANSELH= 0x00;
    TRISC = 0x00;			//Todo el puerto C como salida
    PORTC = 0x00;           //Nos aseguramos que el puerto C esté apagado
    
    while(1){
        RC0 = 1;         	//Enciende  	
    }	
}	