#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);


void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
void lcd_write(unsigned char); //Función que escribe (sin formato) en la LCD.
void lcd_clear(void); //Función que limpia la LCD.
void lcd_goto(unsigned char); //Función que mueve el cursor de la LCD.
void lcd_init(void); //Función que inicializa la LCD.
void lcd_puts(const char *);
void lcd_putch(char);
void lcd_saltoLinea(char ); 

void putch(char); 
char getch(void ); 



#define RX_PIN TRISC7
#define TX_PIN TRISC6


void main(){
    ANSEL=0x00; 
    ANSELH=0x00; 
    INTCON=0x00; 
    TRISA = 0x0F;		//nible menos significativo de PORTA como entrada. 
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    TRISD = 0x00;       //PORTD como salida (pines data de la LCD)
    
    RX_PIN=1; 
    TX_PIN=0; 
    OSCCON=0x70; 
    SPBRG=12; //9600 BAUDIOS.Cambiar para otra cantidad. 
    RCSTA=0x90; //Recepción disponible (SREN=1), 8 Bits, SPEN=1 (Puerto serial habilitados). 
    TXSTA=0x20; //Baja velocidad, SYNC=0 modo asíncrono, TXEN=1, 8 bits.
    BAUDCTL=0x00; //Detector de Baudios deshabilitado, 8 bits, sin inversión, 
    pause(500); 
    
    for(int i=48; i<58; i++){
            putch(i); 
            pause(20); 
        }
        putch(0x0D); 
        putch(0x0A); 
        
        for(int i=97; i<123; i++){
            putch(i); 
            pause(20); 
        }
        putch(0x0D); 
        putch(0x0A); 
        pause(100); 
        lcd_init();
        
        unsigned char pos=0; 

    while(1){
        
        	printf("\r Ingresa un dato:\r\n");
            char input[16];
            char size=0;
            for(int i=0; i<16; i++){
                input[i] = getch();	// read a response from the user

                if(input[i]==10 | input[i]==13) break; 
                size++; 
            }
            lcd_saltoLinea(pos!=0); 
            for(int i=0; i<size; i++) lcd_putch(input[i]); 
            pos=!pos; 
    }
}
        

void putch(char dato){
    while(!TXIF) continue; 
    TXREG=dato; 
}

char getch(){
    while(!RCIF) continue; 
    return RCREG;   
}

void lcd_saltoLinea(char r){
    lcd_goto(r*0x40); 
    lcd_puts("                "); 
    lcd_goto(r*0x40); 
}
