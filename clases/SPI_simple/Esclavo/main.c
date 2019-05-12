#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

#define number 0x30
#define CS RC5

void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
void lcd_write(unsigned char); //Función que escribe (sin formato) en la LCD.
void lcd_clear(void); //Función que limpia la LCD.
void lcd_goto(unsigned char); //Función que mueve el cursor de la LCD.
void lcd_init(void); //Función que inicializa la LCD.
void lcd_puts(const char *);
int comME(char, char); 


char digitos[5]; 

void main(){
    ANSEL = 0x0F;		//nible menos significativo del PORTA como entrada analógica
    ANSELH = 0x00;
    TRISA = 0x2F;		//nible menos significativo de PORTA como entrada. 
    TRISC = 0x18;		//Salidas ccp
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    TRISD = 0xFF;     
    
    CS=1; 
    SSPCON2 = 0x00; 
    SSPSTAT = 0x40;
    SSPCON = 0x14; 
    SSPEN = 1; 
    while(1){
        for(char i=0; i<10; i++){
            PORTB=comME(i, i>0); 
        }
    }
    
}

int comME(char buff, char a){
    if(a) SSPBUF=buff;
    do{} while(!BF);
    return SSPBUF; 
}#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

#define number 0x30
#define CS RC5

void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
void lcd_write(unsigned char); //Función que escribe (sin formato) en la LCD.
void lcd_clear(void); //Función que limpia la LCD.
void lcd_goto(unsigned char); //Función que mueve el cursor de la LCD.
void lcd_init(void); //Función que inicializa la LCD.
void lcd_puts(const char *);
int comME(char, char); 


char digitos[5]; 

void main(){
    ANSEL = 0x0F;		//nible menos significativo del PORTA como entrada analógica
    ANSELH = 0x00;
    TRISA = 0x2F;		//nible menos significativo de PORTA como entrada. 
    TRISC = 0x18;		//Salidas ccp
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    TRISD = 0xFF;     
    
    CS=1; 
    SSPCON2 = 0x00; 
    SSPSTAT = 0x40;
    SSPCON = 0x14; 
    SSPEN = 1; 
    while(1){
        for(char i=0; i<10; i++){
            PORTB=comME(i, i>0); 
        }
    }
    
}

int comME(char buff, char a){
    if(a) SSPBUF=buff;
    do{} while(!BF);
    return SSPBUF; 
}
