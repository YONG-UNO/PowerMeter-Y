//
// Created by DingYong on 2026/3/21.
//

#ifndef POWERMETER_Y_UART_H
#define POWERMETER_Y_UART_H

#include "stm32f1xx_hal.h"

#pragma pack(1)
typedef struct {
    char start;    // 帧头 'X'
    float current; // 电流 (A)
    float voltage; // 电压 (V)
    float power;   // 功率 (W)
    char end;      // 帧尾 'Y'
    uint8_t reserve[5]; // 预留5字节
} frame_t;
#pragma pack()


#endif //POWERMETER_Y_UART_H