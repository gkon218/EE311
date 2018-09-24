/*
 * uart.h
 *
 * Created: 24/09/2018 11:00:21 AM
 *  Author: gkon218
 */ 


#ifndef UART_H_
#define UART_H_



void uart_init(unsigned int prescaler);
void uart_transmit (volatile char* value);
void transmit_string(char* string);

void stopReceive(void);
void startReceive(void);



#endif /* UART_H_ */