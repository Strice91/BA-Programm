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
#include <avr/io.h>
#include <util/delay.h>        // definiert _delay_ms()
#include "BitUtilities.h"

/*-------+---------+---------+---------+---------+---------+---------+---------+
*   Variablen.- und Konstantendefintionen
*--------+---------+---------+---------+---------+---------+---------+---------+*/
#define delay(us)  _delay_loop_2 (((F_CPU/4000)*us)/1000)        // wartet µs

#define Pause1 50
#define DelayTime 100

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

// Init Functions
void lcdInit(void);	
void lcdDisplayClear(void);

// Curser Functions
void lcdCursorInit(void);
void lcdCursorHome(void);
void lcdSetCursorPosition(uint8_t line, uint8_t col);

// 4 Bit Mode Switch
void lcdSwitchToFourBitMode(void);

// Write Functions
void lcdSend8bitMode(unsigned char type, unsigned char c);
void lcdSend4bitMode(unsigned char type, unsigned char c);
void lcdWirteString(char * data);

// Utility Functions
void lcdToggleEnablePin(void);
void delay_ms(uint16_t ms);

