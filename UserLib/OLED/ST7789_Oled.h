//
// Created by 28715 on 2026/4/4.
//

#ifndef GLDRONE_ST7789_OLED_H
#define GLDRONE_ST7789_OLED_H
#include "stdint.h"
#include "main.h"
#include "gpio.h"
#include "spi.h"
#include "fonts.h"

void ST7789_OLED_Init(void);
void ST7789_OLED_Clear(void);
void ST7789_OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void ST7789_OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void ST7789_OLED_ShowNum(uint8_t Line, uint8_t Column,float num);


#endif // GLDRONE_ST7789_OLED_H
