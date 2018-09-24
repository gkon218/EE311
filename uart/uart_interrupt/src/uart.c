/*
 * uart.c
 *
 * Created: 24/09/2018 11:00:03 AM
 *  Author: gkon218
 */ 
#include <asf.h>
#include "uart.h"




void uart_init(unsigned int prescaler){
	//assign the baudrate prescaler
	UBRR0L = prescaler;
	//assign MSBs
	UBRR0H = (prescaler >> 8);
	
	//enable Tx and Rx
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	//enable the interrupt for the receive complete flag
	UCSR0B |= (1 << RXCIE0) | (1<<TXCIE0);
	//configure for 1 stop bit and data size of 8 bits
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	
	sei();
	
	return;
}

void stopReceive(void){
	
	UCSR0B &= ~(1 << RXEN0);
	
	return;
}

void startReceive(void){
	
	UCSR0B |= (1 << RXEN0);
	
	return;
}

void uart_transmit (uint8_t value){
	
	//The function will be stuck in this while loop until the UART data register is empty
	while (! (UCSR0A && (1<<UDRE0)) ){}
	
	//once the UDR is empty the value will be loaded into the UDR to be outputted into the TX pin
	UDR0 = value;
	
}

void transmit_string(char* string){
	uint8_t i = 0;
	sei();
	//while(string[i] <= '\0'){
	while(i < 8){	
		if(string[i] != '\0'){
		uart_transmit(string[i]);
		}
		i++;// = i+2;
	}
}
