/*
 * uart.c
 *
 * Created: 18.03.2015 20:36:18
 *  Author: Strice
 */ 

#include "uart.h"
 
/* 
 * USART Initialization (S 174)
 */
void uart_init(void){
	// Sets the baud rate and the format of the
	// UART transmission. Enables communication

	// Set baud rate
	UBRRnH = UBRR_VAL >> 8;
	UBRRnL = UBRR_VAL & 0xFF;
	// Enable receiver and transmitter
	UCSRnB |= (1<<TXEN0);
	// Set frame format: 8data, 2stop bit
	UCSRnC |= (1<<USBS0)|(3<<UCSZ00);
}
 
/*
 * Sending Frames with 5 to 8 Data Bit (S 174)
 */
void uart_putc(unsigned char data){
	// Sends a single character

	// Wait for empty transmit buffer
	while ( !( UCSRnA & (1<<UDREn)) );
	// Put data into buffer, sends the data
	UDRn = data;
}

/*
 * Receiving Frames with 5 to 8 Data Bits (S 177)
 */
unsigned char uart_receive(void){
	// Receives a single character

	// Wait for data to be received
	while ( !(UCSRnA & (1<<RXCn)) );
	// Get and return received data from buffer
	return UDRn;
}

/*
 * Sending character string
 */
void uart_puts(char *s){
	// Sends a string of chracters as fast as
	// possible

	// 0x00 = end of string
	while (*s){
		// write each char 
		uart_putc(*s); 
		// go to next char
		s++;
	}
}

/*
 * Send two Arrays
 */
/*
void uart_sendTwoArrays(int16_t U[], int16_t I[], int size){
	char str[4];
	int i;
	
	uart_puts("S\n");
	
	for(i=0;i<=999;i++){
		sprintf(str,"%i\n",U[i]);
		uart_puts(str);
	}
	
	for(i=0;i<=999;i++){
		sprintf(str,"%i\n",I[i]);
		uart_puts(str);
	}
	
	uart_puts("E\n");
}*/