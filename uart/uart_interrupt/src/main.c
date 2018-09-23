
#include <asf.h>
#include <stdint.h>
#define F_CPU 16000000UL




#define BAUD 9600
#define BAUD_PRE (F_CPU/BAUD/16) - 1

void uart_init(unsigned int prescaler);
void uart_transmit (uint8_t value);


void uart_init(unsigned int prescaler){
	//assign the baudrate prescaler
	UBRR0H = (BAUD_PRE >> 8);
	UBRR0L = BAUD_PRE;
	
	//enable Tx
	UCSR0B |= (1 << TXEN0);
	//configure for 1 stop bit and data size of 8 bits
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	
	return;
}

void uart_transmit (uint8_t value){
	
	//The function will be stuck in this while loop until the UART data register is empty
	while (! (UCSR0A && (1<<UDRE0)) ){}
	
	//once the UDR is empty the value will be loaded into the UDR to be outputted into the TX pin
	UDR0 = value;
	
}

int main(void){
	uart_init(BAUD_PRE);
	
	while(1){
		uart_transmit('a');
	}
	

	return 0;
}
