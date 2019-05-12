#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

#define number 0x30
#define CS RA5

void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
int comM(char); 


char digitos[5]; 

void main(){
    ANSEL = 0x0F;		//nible menos significativo del PORTA como entrada analógica
    ANSELH = 0x00;
    TRISA = 0x0F;		//nible menos significativo de PORTA como entrada. 
    TRISC = 0x10;		//Salidas ccp
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    TRISD = 0x00;     
    
    CS=1; 
    SSPCON2 = 0x00; 
    SSPSTAT = 0xC0;
    SSPCON = 0x10; 
    SSPEN = 1; 
    
    while(1){
        for(int i=10; i>0; i--){
            PORTB=comM(i); 
            pause(100); 
        }
    }
    
}

int comM(char buffer){
    CS=0;
    SSPBUF=buffer;
    do{} while(!BF);
    CS=1; 
    return SSPBUF; 
}
