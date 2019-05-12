#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);

/*
 *  El programma mide el voltaje de los canales AN0:AN3 (RA0:RA4 respectivamente). 
 *  Cada voltaje medido se muestra en una LCD de 16x2 con la siguiente configuración: 
 *  Modo 4 Bits: Nible menor del PORTC.  
 *  RW a tierra. 
 *  RS: RB0 
 *  Enable: RB1 
 */

void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
void lcd_write(unsigned char); //Función que escribe (sin formato) en la LCD.
void lcd_clear(void); //Función que limpia la LCD.
void lcd_goto(unsigned char); //Función que mueve el cursor de la LCD.
void lcd_init(void); //Función que inicializa la LCD.
void lcd_puts(const char *);
int ADC(char );  //Función que realiza la conversión del canal parámetro.

#define number 0x30

char digitos[5]; 
int volt = 0; //Voltaje en valor sobre 1023.

void main(){
    ANSEL = 0x0F;		//nible menos significativo del PORTA como entrada analógica
    ANSELH = 0x00;
    TRISA = 0x0F;		//nible menos significativo de PORTA como entrada. 
    TRISC = 0x00;		//PORTC como salida (pines data de la LCD)
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    ADCON0 = 0b11000000;	//Fuente Vdd y Vss para el convertidor. 
    ADCON1 = 0x00;	//Justificado a la izquierda.
     
    
    lcd_init();		//Inicializamos el LCD.
    while (1){
        for(int i=0; i<4; i++){ 
            volt=ADC(i);
            sprintf(digitos,"%4.3f", volt*0.004887585); 
            lcd_goto(48*(i>1)+i*8);
            lcd_puts(digitos);  
            pause(25);
        }
       
        pause(150);
    }
}


int ADC(char canal){
    ADCON0= 0xC0;  //Fuente interna, sin canal habilitado, adc deshabilitado.
    ADCON0=ADCON0 |(canal<<2); //Se selecciona el canal. 
    ADON=1; //Se habilita el ADC. 
    NOP();  //Tiempo de adquisición de señal.
    NOP(); 
    NOP(); 
    GO_DONE=1; //Se inicia la conversión.
    while(GO_DONE); //Hasta que se termine la conversión.
    ADON =0; //Se deshabilita el ADC.
    return (ADRESH<<2)|(ADRESL>>6); //Valor del voltaje convertido sobre 1023
}
