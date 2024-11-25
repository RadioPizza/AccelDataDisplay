// ssd1306.h
#ifndef SSD1306_H
#define SSD1306_H

#include "i2c.h"

// Адрес SSD1306 по I2C
#define SSD1306_I2C_ADDRESS 0x78

// Определения команд SSD1306
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

// Прототипы функций
void SSD1306_Init(void);
void SSD1306_Clear(void);
void SSD1306_SetCursor(unsigned char column, unsigned char page);
void SSD1306_WriteChar(char c);
void SSD1306_WriteString(const char *str);
void SSD1306_DrawBitmap(int x, int y, const unsigned char *bitmap, unsigned char width, unsigned char height);
void SSD1306_DisplayOn(void);
void SSD1306_DisplayOff(void);

#endif // SSD1306_H