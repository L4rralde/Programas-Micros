
import serial
import sys
import time  


#Programa para leer y escribir en un puerto COM de forma asíncrona a 96000 BAUDIOS
#Se puede cambiar el puerto. 
SERIAL_PORT = raw_input("Puerto: ")

SERIAL_RATE = 9600
ser = serial.Serial(SERIAL_PORT, SERIAL_RATE)

def main(salto):

    while True:
        reading = ser.read(1).decode('utf-8')
        sys.stdout.write(reading)
        time.sleep(0.05)
        if reading=="\n": 
        	if(salto==1): 
        		break
    		if ser.inWaiting()==0: 
    			break
        	
main(1)
main(1)
while True: 
	main(0)
	salida=raw_input(">>")+"\n"
	for x in salida: 
		ser.write(x)
		time.sleep(0.1)
