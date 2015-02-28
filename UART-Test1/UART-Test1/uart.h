/*
 * uart.h
 *
 * Created: 20.11.2012
 *  Author: Fabi Rosenthal
 */ 
#include <avr/io.h>
 
#ifndef UART_H_
	#define UART_H_
 
//  #define F_CPU	20000000UL	// Clock Speed = 20.000MHz
	#define BAUD	9600UL	// Baud rate
	#define UBRR_VAL	((F_CPU+BAUD*8)/(BAUD*16)-1) // =??
 
	/* Register names USART0 */
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
 
	void uart_puts( char *s );
	void uart_putc( unsigned char data );
	void uart_init( void);
 
#endif /* UART_H_ */