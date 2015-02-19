#include "lcd.h"

// Initialiserung des LDC
void lcdInit(void)
{
	
	//    Initialiserung der Ports
	//    alle Pins als Ausgang
	//    also im Datenrichtungsregister an allen Stelle eine Eins
	//    DDRC |= ( (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6) | (1 << DDC7) );
	LCDDDR = 0xFF;
	
	//    alle Ausgänge auf low
	LCDPORT = 0x00;
	
	delay_ms(20);
	//    Warten damit die Flanke sicher alle fallen
	//    laut Datenblatt reichen 15ms nach erreichen
	//    der Arbeitsspannung von 4,5V aus
	LCDPORT = LCD_INIT;
	//lcdSend8bitMode(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	//    und noch eine Verzögerung weil Busy hier noch nicht ausgewertet werden kann
	delay_ms(10);
	
	//    das Ganze zur Sicherheit noch zwei Mal wiederholen
	//lcdSend8bitMode(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	//lcdSend8bitMode(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	/*
	// Restliche Einstellungen
	lcdDisplayClear();	// Display löschen
	lcdSwitchToFourBitMode();	// In 4 Bit Modus Wechseln
	lcdCursorInit();	// Cursor und Display Einstellungen
	lcdDisplayClear();	// Display löschen
	lcdCursorHome();	// Cursor an HOME Position setzen
	*/
}

void lcdDisplayClear(void)
{
	lcdSend4bitMode(COMMAND,LCD_CLEAR);	// Display löschen
	//    zusätzliche Wartezeit für Löschen
	delay(4000);
}

void lcdCursorInit(void)
{
	lcdSend4bitMode(COMMAND,LCD_DISP);		// Display und Cursor Einstellungen
	lcdSend4bitMode(COMMAND,LCD_MODE);		// Entry Mode Einstellungen
}

void lcdCursorHome(void)
{
	lcdSend4bitMode(COMMAND,LCD_HOME);		// Cursor an die erste Stelle setzen
	//    zusätzliche Wartezeit für Löschen
	delay(4000);
}

// Setzt den Cursor in Zeile y und Spalte x
void lcdSetCursorPosition(uint8_t line, uint8_t col)
{
	uint8_t i;
	switch (line)
	{
		case 1: i=0x80+0x00+col; break;    // 1. line
		case 2: i=0x80+0x40+col; break;    // 2. line
		default: return;                   // invalid line
	}
	lcdSend4bitMode(COMMAND, i);
}

void lcdSwitchToFourBitMode(void)
{
	lcdSend8bitMode(COMMAND,LCD_4_BIT);		// LCD in Vier-Bit_Modus
	lcdSend4bitMode(COMMAND,LCD_SPEC);		// LCD Spezifikationen übertragen
}

// Sendet Daten im 8 Bit Modus
void lcdSend8bitMode(unsigned char type, unsigned char c)
{
	unsigned char sic_c;
	
	sic_c = c;									// Kopie von c
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe Bits
	delay_ms(DelayTime);						// Verzögerung zum Debuggen
	lcdToggleEnablePin();						// Setze Bits gültig
	
}

// Sendet Daten im 4 Bit Modus
void lcdSend4bitMode(unsigned char type, unsigned char c)
{
	unsigned char sic_c;
	
	// Sende die höherwertigen Bits
	sic_c = c;									// Kopie von c
	sic_c = sic_c>>4;							// schiebe die höheren Bits nach unten
	sic_c &= ~0xF0;								// setze höhere bit 7-4 == 0
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe high nibble
	delay_ms(DelayTime);							// Verzögerung zum Debuggen
	lcdToggleEnablePin();						// Setze Bits gültig
	
	// Sende die niederwertigen Bits
	sic_c = c;									// Kopie von c
	sic_c &= ~0xF0;								// set bit 7-4 == 0
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe low nibble
	delay_ms(DelayTime);							// Verzögerung zum Debuggen
	lcdToggleEnablePin();						// Setze Bits gültig
	
}

// Schreibt einen String zum LCD
void lcdWirteString(char *data)
{
	while(*data)
	{
		lcdSend4bitMode(DATA, *data);
		data++;
	}
}

void lcdToggleEnablePin(void)
{
	sbi(LCDPORT,PIN_E);		// Enableleitung (PIN_E) auf high legen
	delay(100);				// Warten damit die Flanke sicher entsteht
	
	delay_ms(Pause1);		// Verzögerung zum Debuggen
	
	cbi(LCDPORT,PIN_E);		// Enableleitung (PIN_E) wieder auf low legen
	delay(200);				// Warten damit die Flanke sicher gefallen ist
	
	delay_ms(Pause1);		// Verzögerung zum Debuggen
}

void delay_ms(uint16_t ms)
{
	for(uint16_t t=0; t<ms; t++)
	_delay_ms(1);
}