//
// Created by 28715 on 2026/4/4.
//

#ifndef POWERMETER_Y_FONTS_H
#define POWERMETER_Y_FONTS_H

#include <stdint.h>

typedef struct {
    const uint8_t width;
    uint8_t height;
    const uint16_t *data;
} FontDef;


extern FontDef Font_7x10;
extern FontDef Font_11x18;
extern FontDef Font_16x26;


#endif // POWERMETER_Y_FONTS_H
