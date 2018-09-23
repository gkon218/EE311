
#include <asf.h>
#define F_CPU 16000000UL  
#include <avr/io.h>
#include <stdint.h>                     
#include <avr/interrupt.h>
#include <util/delay.h>
                    
#define BAUD 9600
#define BAUD_PRE (( (F_CPU/BAUD)/16 ) -1 )
#define MAX_COMMAND_SIZE 20

volatile char commandChar[MAX_COMMAND_SIZE];
volatile uint8_t charCount = 0;
volatile uint8_t receivedCommand = 0;
volatile char testChar;


void uart_init(unsigned int prescaler);
void uart_transmit (uint8_t value);
void transmit_string(char* string);

void uart_init(unsigned int prescaler){
	//assign the baudrate prescaler
	UBRR0H = (BAUD_PRE >> 8);
	UBRR0L = BAUD_PRE;
		
	//enable Tx and Rx
	UCSR0B |= (1 << TXEN0)     ;//;| (1 << RXEN0);
	//enable the interrupt for the receive complete flag
	UCSR0B |= (1 << RXCIE0);
	//configure for 1 stop bit and data size of 8 bits
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	//enable global interrupts
	sei();
	
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
	while(string[i] != '\0'){
		uart_transmit(string[i]);
		i++;
	}
}

#define LED_ON PORTC |= (1<<PORTC0)
#define LED_OFF PORTC &= ~(1<<PORTC0)

int main( void )
{
    board_init();
	uart_init(BAUD_PRE);
	
	DDRC |= (1<<DDC0);           
					  
					    
	while(1)
	{
		     //if(receivedCommand){
				 ////turn of Rx interrupt while transmitting
				 //UCSR0B &= ~(1 << RXCIE0);
				 //uart_transmit('a');
				 //charCount = 0; //reset the index counter for the next command
			 //} 
			 //LED_ON;
			 uart_transmit(0x41);
			 //transmit_string("test... ");
			 //
			 //if(receivedCommand){
				//UCSR0B &= !(1 << RXEN0);
				 //_delay_ms(10);
				//transmit_string("received some character... ");
				//receivedCommand = 0;
				//UCSR0B |= (1 << RXEN0);
			 //}       
			 //_delay_ms(200);
			 //LED_OFF;
			 //_delay_ms(200);
			   //
	}
}

ISR (USART_RX_vect)
{
	//testChar = UDR0;
	receivedCommand++;
	
}
//ISR (USART_RX_vect)
//{
	////copy the character into index number charCount of the command character array
	//commandChar[charCount] = UDR0;
	//if( (commandChar[charCount] == '\0')|| (commandChar[charCount] == '\n')|| (commandChar[charCount] == '\r') ){
		////write logic high to the received command variable to notify while loop to 
		////	compare for a valid command
		//receivedCommand++;
	//}
	////increment the index number to get ready for the next character
	//charCount++;
	////if the index number is equal to or greater than the maximum command size,
	////	then reset the index number to zero and overwrite the command 
	//if(charCount >= MAX_COMMAND_SIZE){
		//charCount = 0;
	//}
//}
