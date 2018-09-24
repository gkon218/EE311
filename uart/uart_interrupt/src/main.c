
#include <asf.h>
#define F_CPU 16000000UL

#define BAUD 9600
#define BAUD_PRE (F_CPU/BAUD/16) - 1

#include <stdint.h>
#include <avr/interrupt.h>

#include "uart.h"

#define MAX_BUFFER_SIZE 50


volatile uint8_t charCount = 0;
volatile char* testChar[MAX_BUFFER_SIZE];
volatile uint8_t receivedCommand;
volatile uint8_t commandReceived = 0; 


ISR (USART_RX_vect)
{
	testChar[charCount] = UDR0;
	charCount++;
	if (charCount >= MAX_BUFFER_SIZE){
		commandReceived = 1;
		charCount = 0;
		cli();
	}
}

char ReceivedChar;


int main(void){
	board_init();
	uart_init(BAUD_PRE);

	sei();

	while(1){
		if(commandReceived){
			commandReceived = 0;
			uart_transmit('b');
			sei();
		}
	}
	return 0;
}


