/*
 * uart.h
 *
 * Created: 24/09/2018 11:00:21 AM
 *  Author: gkon218
 */ 


#ifndef UART_H_
#define UART_H_



void uart_init(unsigned int prescaler);
void uart_transmit (uint8_t value);
void transmit_string(char* string);



#endif /* UART_H_ */