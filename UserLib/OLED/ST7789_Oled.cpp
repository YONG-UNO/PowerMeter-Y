//
// Created by 28715 on 2026/4/4.
//

#include "ST7789_Oled.h"
void ST7789_OLED_Init(void) {

   ST7789_BL_HIGH();
   ST7789_CS_HIGH();

   ST7789_RST_HIGH();
   ST7789_RST_LOW();
   HAL_Delay(1);
   ST7789_RST_HIGH();
   HAL_Delay(120);

   ST7789_SendByte(0x11, ST7789_CMD);

   ST7789_SendByte(0x3A, ST7789_CMD);
   ST7789_SendByte(0x55, ST7789_DATA);   //   5 565  6 666

   ST7789_SendByte(0xB2, ST7789_CMD);
   ST7789_SendByte(0x0C, ST7789_DATA);
   ST7789_SendByte(0x0C, ST7789_DATA);
   ST7789_SendByte(0x00, ST7789_DATA);
   ST7789_SendByte(0x33, ST7789_DATA);
   ST7789_SendByte(0x33, ST7789_DATA);

   ST7789_SendByte(0xB7, ST7789_CMD);
   ST7789_SendByte(0x35, ST7789_DATA);

   ST7789_SendByte(0xBB, ST7789_CMD);
   ST7789_SendByte(0x32, ST7789_DATA); //Vcom=1.35V

   ST7789_SendByte(0xC2, ST7789_CMD);
   ST7789_SendByte(0x01, ST7789_DATA);

   ST7789_SendByte(0xC3, ST7789_CMD);
   ST7789_SendByte(0x19, ST7789_DATA); //GVDD=4.8V

   ST7789_SendByte(0xC4, ST7789_CMD);
   ST7789_SendByte(0x20, ST7789_DATA); //VDV, 0x20:0v

   ST7789_SendByte(0xC6, ST7789_CMD);
   ST7789_SendByte(0x0F, ST7789_DATA); //0x0F:60Hz

   ST7789_SendByte(0xD0, ST7789_CMD);
   ST7789_SendByte(0xA4, ST7789_DATA);
   ST7789_SendByte(0xA1, ST7789_DATA);

   ST7789_SendByte(0xE0, ST7789_CMD);
   ST7789_SendByte(0xD0, ST7789_DATA);
   ST7789_SendByte(0x08, ST7789_DATA);
   ST7789_SendByte(0x0E, ST7789_DATA);
   ST7789_SendByte(0x09, ST7789_DATA);
   ST7789_SendByte(0x09, ST7789_DATA);
   ST7789_SendByte(0x05, ST7789_DATA);
   ST7789_SendByte(0x31, ST7789_DATA);
   ST7789_SendByte(0x33, ST7789_DATA);
   ST7789_SendByte(0x48, ST7789_DATA);
   ST7789_SendByte(0x17, ST7789_DATA);
   ST7789_SendByte(0x14, ST7789_DATA);
   ST7789_SendByte(0x15, ST7789_DATA);
   ST7789_SendByte(0x31, ST7789_DATA);
   ST7789_SendByte(0x34, ST7789_DATA);

   ST7789_SendByte(0xE1, ST7789_CMD);
   ST7789_SendByte(0xD0, ST7789_DATA);
   ST7789_SendByte(0x08, ST7789_DATA);
   ST7789_SendByte(0x0E, ST7789_DATA);
   ST7789_SendByte(0x09, ST7789_DATA);
   ST7789_SendByte(0x09, ST7789_DATA);
   ST7789_SendByte(0x15, ST7789_DATA);
   ST7789_SendByte(0x31, ST7789_DATA);
   ST7789_SendByte(0x33, ST7789_DATA);
   ST7789_SendByte(0x48, ST7789_DATA);
   ST7789_SendByte(0x17, ST7789_DATA);
   ST7789_SendByte(0x14, ST7789_DATA);
   ST7789_SendByte(0x15, ST7789_DATA);
   ST7789_SendByte(0x31, ST7789_DATA);
   ST7789_SendByte(0x34, ST7789_DATA);

   ST7789_SendByte(0x21, ST7789_CMD);

   ST7789_SendByte(0x36, ST7789_CMD); //MX, MY, RGB mode
#if (ST7789_ROTATION == 0)
   ST7789_SendByte(0x00, ST7789_DATA);
#elif (ST7789_ROTATION == 90)
   ST7789_SendByte(0x60, ST7789_DATA);//90
#elif (ST7789_ROTATION == 180)
   ST7789_SendByte(0xC0, ST7789_DATA);//180
#elif (ST7789_ROTATION == 270)
   ST7789_SendByte(0xA0, ST7789_DATA);//270
#endif

   ST7789_SendByte(0x2A, ST7789_CMD); //Column Address Set
   ST7789_SendByte(0x00, ST7789_DATA);
   ST7789_SendByte(0x00, ST7789_DATA); //0
   ST7789_SendByte(0x00, ST7789_DATA);
   ST7789_SendByte(0xEF, ST7789_DATA); //239

   ST7789_SendByte(0x2B, ST7789_CMD); //Row Address Set
   ST7789_SendByte(0x00, ST7789_DATA);
   ST7789_SendByte(0x00, ST7789_DATA); //0
   ST7789_SendByte(0x00, ST7789_DATA);
   ST7789_SendByte(0xEF, ST7789_DATA); //239

   ST7789_SendByte(0x29, ST7789_CMD);
}
void ST7789_OLED_Clear(void) {

}
void ST7789_OLED_ShowChar(uint8_t Line, uint8_t Column, char Char) {

}
void ST7789_OLED_ShowString(uint8_t Line, uint8_t Column, char *String) {

}
void ST7789_OLED_ShowNum(uint8_t Line, uint8_t Column,float num) {

}
