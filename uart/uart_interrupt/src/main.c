
#include <asf.h>
#define F_CPU 16000000UL

#define BAUD 9600
#define BAUD_PRE (F_CPU/BAUD/16) - 1

#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uart.h"

#define MAX_BUFFER_SIZE 50


volatile uint8_t recIndex = 0;
volatile char* command[MAX_BUFFER_SIZE];
volatile uint8_t receivedCommand;
volatile uint8_t commandReceived = 0; 
volatile uint8_t charIndex = 0;
       

volatile char* test[MAX_BUFFER_SIZE] = { '{','a','b','c','d','e','}'};


ISR (USART_RX_vect)
{

	
	command[recIndex] = UDR0;
	
	//uart_transmit(charCount);
	if (recIndex >= MAX_BUFFER_SIZE){
		commandReceived = 1;
		cli();
		UCSR0B |= (1 << TXEN0); 
		uart_transmit('&');
		
	}
	else if (command[recIndex] == 'd'){
		commandReceived = 1;
		cli();
		UCSR0B |= (1 << TXEN0); 
		uart_transmit('\0');
		
	}
	recIndex++;
	
}


ISR (USART_TX_vect)
{
		commandReceived = 0;
		
	uart_transmit(test[charIndex]);
	//if(charIndex == recIndex){
	if (charIndex >= strlen(test)){
		//uart_transmit('_');
		recIndex = 0;
			charIndex = 0;
		//cli();
		UCSR0B &= ~(1 << TXEN0); 
		
	}
	charIndex++;
}

int main(void){
	board_init();
	uart_init(BAUD_PRE);

	while(1){
	
	}
	
	return 0;
}


