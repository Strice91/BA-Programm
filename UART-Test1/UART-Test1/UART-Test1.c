/*
 * UART_Test1.c
 *
 * Created: 28.02.2015 21:04:41
 *  Author: Strice
 */ 


#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>

int main(void)
{
	uart_init();
	
	while(1)
	{
		_delay_ms(100);
		uart_puts("Hallo");
	}
}