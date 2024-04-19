//***********************************************************************************************
// Universidad del Valle de Guatemala
// IE2023: Programación de Microcontroladores
// Autor: Héctor Martínez - 22369
// Proyecto: prelab 6
// Hardware: atmega328p
//***********************************************************************************************

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void initUART9600(void);
void writeUART(char Character);
uint8_t bufferTX;
int main(void)
{
	initUART9600();
	writeUART('H');
	writeUART('O');
	writeUART('L');
	writeUART('A');
	writeUART('\n');
	while (1) 
    {
    }
}

void initUART9600(void){
	//Pin TX salida y RX salida
	DDRD &= ~(1<<DDD0);
	DDRD |= (1<<DDD1);
	
	//Configurar UCSR0A
	UCSR0A = 0;
	
	//Configurar UCSR0B, habilitar ISR de recepción, rx y tx
	UCSR0B = 0;
	
	UCSR0B |= (1<<RXCIE0) | (1<<RXEN0)| (1<<TXEN0);
	//Configurar UCSR0C asíncrono, no paridad, 1 bit stop, data bits 8/bits
	UCSR0C = 0;
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	
	//Configurar velocidad de Buadrate: 9600
	UBRR0 = 113;
		
}

void writeUART(char Character){
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0 = Character;
	
}

ISR(USART_RX_vect){
	bufferTX = UDR0;
	while(!(UCSR0A &(1<<UDRE0)));
	UDR0 = bufferTX;
}