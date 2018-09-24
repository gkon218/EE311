
#include <asf.h>
#define F_CPU 16000000UL

#define BAUD 9600
#define BAUD_PRE (F_CPU/BAUD/16) - 1

#include <stdint.h>
#include <avr/interrupt.h>

#include "uart.h"

#define MAX_BUFFER_SIZE 50


volatile uint8_t charCount = 0;
volatile char* command[MAX_BUFFER_SIZE];
volatile uint8_t receivedCommand;
volatile uint8_t commandReceived = 0; 


ISR (USART_RX_vect)
{

	
	command[charCount] = UDR0;
	
	//uart_transmit(charCount);
	if (charCount >= MAX_BUFFER_SIZE){
		commandReceived = 1;
		cli();
	}
	else if (command[charCount] == 'd'){
		commandReceived = 1;
		cli();
	}
	charCount++;
}

ISR (USART_TX_vect)
{

	
	//command[charCount] = UDR0;
	
	//uart_transmit(charCount);
	if (charCount >= MAX_BUFFER_SIZE){
		commandReceived = 1;
		cli();
	}
	else if (command[charCount] == 'd'){
		commandReceived = 1;
		cli();
	}
	charCount++;
}


char ReceivedChar;


int main(void){
	board_init();
	uart_init(BAUD_PRE);

	sei();

	while(1){
		if(commandReceived){
			commandReceived = 0;
			charCount = 0;
			//transmit_string("received ");
			transmit_string(command);
			//uart_init(BAUD_PRE);
			sei();
		}
	}
	return 0;
}


