/*
 * UART_Test1.c
 *
 * Created: 28.02.2015 21:04:41
 *  Author: Strice
 */ 


#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include <util/delay.h>

int c;
char str[4];

int main(void)
{
	uart_init();
	
	while(1)
	{
		uart_puts("S\n");
		
		for(c=1;c<=100;c++){
			sprintf(str,"%d\n",c);
			uart_puts(str);
		}
		
		uart_puts("E\n");
		
		_delay_ms(100);
	}
	
}