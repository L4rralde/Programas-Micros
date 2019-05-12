#include<htc.h>
#include<stdio.h>

__CONFIG (FOSC_INTRC_NOCLKOUT & WDTE_OFF & PWRTE_OFF & MCLRE_OFF & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF & LVP_OFF & DEBUG_OFF);
__CONFIG (BOR4V_BOR40V & WRT_OFF);
/*
 *  Este circuito lee los canales AN0 y AN1 (RA0 y RA1 respectivamente). 
 *  Utiliza el nible menor del PORTD para escribir en una LCD 16x2 en modo de 4 bits. 
 *  RS es RB0, RW está aterrizado a tierra y EN en RB1. 
 *  Se programa el PWM con frecuencia constante y ciclo de trabajo variable que deende de
 *  las conversions ADC realizadas.
 *  En la LCD se muestran Voltaje, porcentaje del ciclo de trbaajo y frecuencia del PWM.
 */
void msecbase(void); //Retardo de un ms. 
void pause(unsigned short msvalue); //Retardo de msvalue ms. 
void lcd_write(unsigned char); //Función que escribe (sin formato) en la LCD.
void lcd_clear(void); //Función que limpia la LCD.
void lcd_goto(unsigned char); //Función que mueve el cursor de la LCD.
void lcd_init(void); //Función que inicializa la LCD.
void lcd_puts(const char *);
int ADC(char); 


#define number 0x30

char digitos[5]; 
int volt[2]; //Voltaje en valor sobre 1023.
int frec=980;
char adres[2];
char ccpcon[2]={0x0C, 0x0C};

void main(){
    
    ANSEL = 0x0F;		//nible menos significativo del PORTA como entrada analógica
    ANSELH = 0x00;
    TRISA = 0x0F;		//nible menos significativo de PORTA como entrada. 
    TRISC = 0x00;		//Salidas ccp
    TRISB = 0x00;       //PORTB como salida (RE y RS)
    TRISD = 0x00;       //PORTD como salida (pines data de la LCD)

    ADCON0 = 0b11000000;	//Fuente Vdd y Vss para el convertidor. 
    ADCON1 = 0x00;	//Justificado a la izquierda.
    
    PR2 = 0xFE; 
    CCP1CON = 0x0C; 
    CCP2CON = 0x0C; 
    T2CON = 0x07;
    
    lcd_init();		//Inicializamos el LCD.
    while (1){
        for(int i=0; i<2; i++){
            volt[i]=ADC(i);
            adres[i]=ADRESH;
            ccpcon[i]=(0x0C)|((ADRESL>>2)&0x30);
            pause(25); 
        }
        CCPR1L = adres[0];
        CCP1CON= ccpcon[0];
        CCPR2L = adres[1];
        CCP2CON= ccpcon[1];

        for(int i=0; i<2; i++){
            int cursor=(i>0)*0x40; 
            lcd_goto(0x00+cursor); 
            sprintf(digitos,"%3.2f", volt[i]*0.004887585);  
            lcd_puts(digitos);
            lcd_puts("V");
            sprintf(digitos,"%3i", 25*volt[i]/PR2);
            lcd_goto(0x06+cursor);
            lcd_puts(digitos);
            lcd_puts("%");
            sprintf(digitos, "%5i", frec);
            lcd_goto(0x0A+cursor);
            lcd_puts(digitos); 
        }
        pause(50);
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
