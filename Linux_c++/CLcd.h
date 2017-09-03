/*
 * CLcd.h
 *
 *  Created on: 31/01/2017
 *      Author: hacked
 */

#ifndef CLCD_H_
#define CLCD_H_

#include "Header.h"

// Defines for the interface
#define I2C_ADDR   0x20 // I2C device address
// Define some device constants
#define LCD_CHR  0x10 // Mode - Sending data
#define LCD_CMD  0 // Mode - Sending command
#define LINE1  0x80 // 1st line
#define LINE2  0xC0 // 2nd line
#define ENABLE 0x40 // Enable bit

class CLcd {
private:
	void LcdInit(void); //Initialize the LCD
	void LcdByte(int bits, int mode);
	void LcdToggleEnable(int bits);

	// added by Lewis
	void LcdLoc(int line); //move cursor
	void ClrLcd(void); // clr LCD return home
	void Typeln(const char *s);

public:
	CLcd();
	~CLcd();
	static void * Display(void* args);		//Behaviour for the Thread tDisplay
};

#endif /* CLCD_H_ */
