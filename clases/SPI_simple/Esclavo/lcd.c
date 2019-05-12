#include<htc.h>

#define	LCD_RS RB0
#define LCD_EN RB1
#define LCD_DATA	PORTD
#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

void msecbase(){
    //La siguiente línea fue la única que se cambió. Antes estaba como OPTION. 
    //En el PIC16F887 se llama OPTION_REG.
	OPTION_REG = 0b00000001;		//Set prescaler to TMRO 1:4
	TMR0 = 0x07;					//Preset TMRO to overflow on 250 counts
	while(!T0IF);				//Stay until TMRO overflow flag equals 1
	T0IF = 0;					//Clear the TMR0 overflow flag
}

void pause( unsigned short msvalue ){
	for (unsigned short x=0; x<=msvalue; x++) msecbase();				//Jump to millisec delay routine
}



void lcd_write(unsigned char c) {
	pause (1);
	LCD_DATA = ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA = ( c & 0x0F );
	LCD_STROBE();
	
}

void lcd_clear(){
	LCD_RS = 0;
	lcd_write(0x1);
	pause (2);
}

void lcd_goto(unsigned char pos){
	LCD_RS = 0;
	lcd_write(0x80+pos);
}

void lcd_init(){
	char init_value;
	init_value = 0x3;
	TRISB=0;
	TRISC=0;
	LCD_RS = 0;
	LCD_EN = 0;
	pause (15);				
	LCD_DATA	 = init_value;
	LCD_STROBE();
	pause(10);
	LCD_STROBE();
	pause(10);
	LCD_STROBE();
	pause(10);
	LCD_DATA = 2;	//Modo de 4 bits.
	LCD_STROBE();
	
	lcd_write(0x28); //Se establece el tamaño de la interfaz.
	lcd_write(0xC); //Display encendido, cursor encendido, modo blink. 
	lcd_clear();	
	lcd_write(0x6); //Se establece el modo de entrada.
}

void lcd_puts(const char * s){
	LCD_RS = 1;	// write characters
	while(*s) lcd_write(*s++);
}
