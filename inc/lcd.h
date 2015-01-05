/*-------+---------+---------+---------+---------+---------+---------+---------+
*
*    Datei:      lcd.h
*    erstellt:   im Januar 2010
*    von:        Bot-Builder
*
*    Hardware:   Bot-Board ATMega 16 V2
*				 ATMega 32 und 7,3728 Mhz,
*                Bot-Board LC-Display V1,
*                Bot-Board Portanzeige mit LED
*
*    Resourcen
*
*    Timer0:        frei
*
*    Timer1:        frei
*
*    Timer2:        frei
*
*
*    Interrupt:    keine
*
*    I/O-Pins:
*
*
*    Funktionsbeschreibung:
*        In diesem Programm wird die vollständige  Initialisierung des
*        LC-Display ohne Verwendung von Biblotheken abgearbeitet.
*        Zum Debuggen wurden Verzögerungen verwendet.
*        Das LC-Display ist wie folgt angeschlossen:
*            PC3        DB7
*            PC2        DB6
*            PC1        DB5
*            PC0        DB4
*						DB3        an gnd
*						DB2        an gnd
*						DB1        an gnd
*						DB0        an gnd
*            PC4        Enable Hintergrundbeleuchtung
*            PC5        E (Taktleitung)
*            PC6        R/W
*            PC7        RS
*
*        Zur Kontrolle werden auf Port D die gleichen Daten ausgegeben
*        und mit den LEDs dargestellt.
*
*        Das Display wird somit im 4-Bit Modus verwendet.
*
*        JTAG Interface mit den Fuses ausgeschaltet!
*        sonst funktioniert Port C nicht vollständig.
*
*        Bei dieser Beschaltung kann das Busyflag ausgelesen werden!
*
*
*
*    Bemerkungen:
*
*
*    letzte Änderung: 25.01.2010
*
*
---------+---------+---------+---------+---------+---------+---------+---------+*/

// #include-Dateien
#include <util/delay.h>        // definiert _delay_ms()
#include "BitUtilities.h"

/*-------+---------+---------+---------+---------+---------+---------+---------+
*   Variablen.- und Konstantendefintionen
*--------+---------+---------+---------+---------+---------+---------+---------+*/
#define delay(us)  _delay_loop_2 (((F_CPU/4000)*us)/1000)        // wartet µs

#define Pause1 1

// definitions of port pins
#define	LCDPORT			PORTC
#define	LCDDDR			DDRC

#define PIN_D4			PC0
#define PIN_D5			PC1
#define PIN_D6			PC2
#define PIN_D7			PC3

#define PIN_E			PC5
#define PIN_RW			PC6
#define PIN_RS			PC7

#define	COMMAND			0
#define DATA			1

// LCD control cmmands 

// Initialisierung des LC-Displays zunächst in den 8-Bit Modus schalten
// DB7 = 0, DB6 = 0 und DB5 = 1 schaltet in die Funktionsdefinition um, 
// dann bedeutet DB4 = 1, 8-Bit-Modus DB3 bis DB0 liegen fest auf gnd
// zunächst also die Daten ans LC-Display legen, RS und R/W bleiben null
// also PC2 und PC3 auf high also muss 0b 0000 1100 (mit RS und R/W = 0)
// übertragen werden
#define LCD_INIT		0x0C	//	0b 0000 1100

//    und jetzt in den 4-Bit-Modus schalten
//    also DB5 = 1 und DB4 = 0
//    also PC2 = 1 und PC3 = 0
//    also 0b 0000 0100
//    mit RS und R/W = 0
#define LCD_4_BIT		0x04	//	0b 0000 0100

//    die übrigen Betriebsparameter einstellen
//    Funktionsdefinition     0b 001
//    4-Bit                         0
//    2/4zeiliges Display             1
//    5x7 Dots Zeichen                 0
//    unerheblich                       00
//    also                    0b 0010 1000
//    muss übertragen werden
#define LCD_SPEC		0x28	//	0b 0010 1000

//    Display/Cursor          0b 0000 1
//    Display an                       1
//    Cursor an                         1
//    Cursor blinken                     1
//    also                    0b 0000 1111
//    muss übertragen werden
#define LCD_DISP		0x0F	//	0b 0000 1111

//    Modus festlegen						0b 0000 01
//    Cursorposition inkrementieren					  1
//    Displayshift						               0
//    also									0b 0000 0110
//    muss übertragen werden
#define LCD_MODE		0x06	//	0b 0000 0110

#define LCD_CLEAR		0x01	//	0b 0000 0001

#define LCD_HOME		0x02	//	0b 0000 0010


/*-------+---------+---------+---------+---------+---------+---------+---------+
*   delay_ms(ms):
*        wartet ms Millisekunden
*--------+---------+---------+---------+---------+---------+---------+---------+*/
void delay_ms(uint16_t ms)
{
	for(uint16_t t=0; t<=ms; t++)
	_delay_ms(1);
}

void toggle_enable_pin(void)
{
	sbi(LCDPORT,PIN_E);		// Enableleitung (PIN_E) auf high legen
	delay(100);				// Warten damit die Flanke sicher entsteht
	
	delay_ms(Pause1);		// Verzögerung zum Debuggen
	
	cbi(LCDPORT,PIN_E);		// Enableleitung (PIN_E) wieder auf low legen
	delay(200);				// Warten damit die Flanke sicher gefallen ist
	
	delay_ms(Pause1);		// Verzögerung zum Debuggen
}

// Sendet Daten im 4 Bit Modus
void lcdSend4(unsigned char type, unsigned char c)
{
	unsigned char sic_c;					
	
	// Sende die höherwertigen Bits
	sic_c = c;									// Kopie von c
	sic_c = sic_c>>4;							// schiebe die höheren Bits nach unten
	sic_c &= ~0xF0;								// setze höhere bit 7-4 == 0
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe high nibble
	delay_ms(Pause1);							// Verzögerung zum Debuggen
	toggle_enable_pin();						// Setze Bits gültig
	
	// Sende die niederwertigen Bits
	sic_c = c;									// Kopie von c 
	sic_c &= ~0xF0;								// set bit 7-4 == 0
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe low nibble
	delay_ms(Pause1);							// Verzögerung zum Debuggen
	toggle_enable_pin();						// Setze Bits gültig
	
}

// Sendet Daten im 8 Bit Modus
void lcdSend8(unsigned char type, unsigned char c)
{
	unsigned char sic_c;
	
	sic_c = c;									// Kopie von c
	if (type==DATA) sic_c |= (1<<PIN_RS);		// data: RS = 1
	LCDPORT = sic_c;							// schreibe Bits
	delay_ms(Pause1);							// Verzögerung zum Debuggen
	toggle_enable_pin();						// Setze Bits gültig
	
}

// Schreibt einen String zum LCD
void lcdWrite(char *data)
{
	while(*data)
	{
		lcdSend4(DATA, *data);
		data++;
	}
}

// Setzt den Cursor in Zeile y und Spalte x
void lcdSetCursor(uint8_t line, uint8_t col)
{
	uint8_t i;
	switch (line)
	{ 
		case 1: i=0x80+0x00+col; break;    // 1. line
		case 2: i=0x80+0x40+col; break;    // 2. line
		default: return;                   // invalid line
	}
	lcdSend4(COMMAND, i);
}

void fourBitMode(void)
{
	lcdSend8(COMMAND,LCD_4_BIT);	// LCD in Vier-Bit_Modus
	lcdSend4(COMMAND,LCD_SPEC);		// LCD Spezifikationen übertragen
}

void initCursor(void)
{
	lcdSend4(COMMAND,LCD_DISP);		// Display und Cursor Einstellungen
	lcdSend4(COMMAND,LCD_MODE);		// Entry Mode Einstellungen
}

void clearDisplay(void)
{
	lcdSend4(COMMAND,LCD_CLEAR);	// Display löschen
	//    zusätzliche Wartezeit für Löschen
	delay(4000);
}

void cursorHome(void)
{
	lcdSend4(COMMAND,LCD_HOME);		// Cursor an die erste Stelle setzen
	//    zusätzliche Wartezeit für Löschen
	delay(4000);
}

// Init LCD
void initLDC(void)
{
	//    Initialiserung der Ports
	//    alle Pins als Ausgang
	//    also im Datenrichtungsregister an allen Stelle eine Eins
	//    DDRC |= ( (1 << DDC0) | (1 << DDC1) | (1 << DDC2) | (1 << DDC3) | (1 << DDC4) | (1 << DDC5) | (1 << DDC6) | (1 << DDC7) );
	LCDDDR = 0xFF;
	
	//    alle Ausgänge auf low
	LCDPORT = 0x00;
	
	//    Warten damit die Flanke sicher alle fallen
	//    laut Datenblatt reichen 15ms nach erreichen
	//    der Arbeitsspannung von 4,5V aus
	delay_ms(100);
	
	lcdSend8(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	
	//    und noch eine Verzögerung weil Busy hier noch nicht ausgewertet werden kann
	delay_ms(5);
	
	//    das Ganze zur Sicherheit noch zwei Mal wiederholen
	lcdSend8(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	lcdSend8(COMMAND,LCD_INIT);		// Initialisierung des LC-Displays
	
	// Restliche Einstellungen
	fourBitMode();	// In 4 Bit Modus Wechseln
	initCursor();	// Cursor und Display Einstellungen
	clearDisplay();	// Display löschen
	cursorHome();	// Cursor an HOME Position setzen
	
}