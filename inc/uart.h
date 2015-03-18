/*
 * uart.h
 *
 * Created: 18.03.2015 20:36:18
 *  Author: Strice
 */ 

#ifndef UART_H
 	#define UART_H

 	#include <avr/io.h>
	#include <stdio.h>
 
	#define BAUD		115200UL
	#define UBRR_VAL	((F_CPU+BAUD*8)/(BAUD*16)-1)
 
 	// Adjust general names to register 0
	#define UBRRnH	UBRR0H
	#define UBRRnL	UBRR0L
 
	#define UCSRnA	UCSR0A
	#define UCSRnB	UCSR0B
	#define UCSRnC	UCSR0C
 
	#define UDRn	UDR0
	#define UDREn	UDRE0
	#define UPEn	UPE0
 
	#define DORn	DOR0
	#define FEn		FE0
	#define RXCn	RXC0
	#define TXB8	TXB80
 
 	// Sets the baud rate and the format of the
	// UART transmission. Enables communication
 	void uart_init(void);

 	// Sends a single character
 	void uart_putc(unsigned char data);

 	// Receives a single character
	unsigned char uart_receive(void);

	// Sends a string of chracters as fast as
	// possible
	void uart_puts(char *s);


	//void uart_sendTwoArrays(int16_t *U, int16_t *I, int size);
 
#endif //UART_H