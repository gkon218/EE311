
#include <asf.h>
#define F_CPU 16000000UL

#define BAUD 9600
#define BAUD_PRE (F_CPU/BAUD/16) - 1

#include <stdint.h>
#include <avr/interrupt.h>

#include "uart.h"




volatile char testChar;
volatile uint8_t receivedCommand;



int main(void){
	board_init();
	uart_init(BAUD_PRE);
	
	while(1){

		
	}
	

	return 0;
}

ISR (USART_RX_vect)
{
	testChar = UDR0;
	UDR0 = testChar;
	//receivedCommand++;	
}
