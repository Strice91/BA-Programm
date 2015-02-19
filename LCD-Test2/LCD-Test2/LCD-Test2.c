/*
 * LCD_Test2.c
 *
 * Created: 19.02.2015 12:23:53
 *  Author: Strice
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "lcd.h"

int i;
char str[4];

int main(void)
{
	lcdInit();
	/*i = 0;
	while(1){
		i++;
		if(i>9999){
			i = 0;
		}
		sprintf(str,"%02d",i);
		lcdSetCursorPosition(1,0);
		lcdWirteString(str);
	}*/
}