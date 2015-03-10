/*
 * uart.c
 *
 * Created: 20.11.2012
 * Author: Fabi Rosenthal, Florian T.
 */ 
#include "uart.h"
 
/* 
 * USART Initialization (Datasheet page 178)
 */
void uart_init(void){
	/* Set baud rate */
	UBRRnH = UBRR_VAL >> 8;
	UBRRnL = UBRR_VAL & 0xFF;
	/* Enable receiver and transmitter */
	UCSRnB |= (1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSRnC |= (1<<USBS0)|(3<<UCSZ00);
}
 
/*
 * Sending Frames with 5 to 8 Data Bit (Datasheet page 179)
 */
void uart_putc(unsigned char data){
	/* Wait for empty transmit buffer */
	while ( !( UCSRnA & (1<<UDREn)) );
	/* Put data into buffer, sends the data */
	UDRn = data;
}
 
/*
 * Sending strings
 */
void uart_puts(char *s){
	/* while *s != '\0' so unequally "string-end characters (terminator) */
	while (*s){
		uart_putc(*s);
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