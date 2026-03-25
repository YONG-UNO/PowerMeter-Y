//
// Created by DingYong on 2026/3/21.
//

#ifndef POWERMETER_Y_UART_H
#define POWERMETER_Y_UART_H

#include "stm32f1xx_hal.h"

#pragma pack(push,1) // push:将前面的对齐方式保存,1字节对齐
typedef struct {
    char start;    // 帧头 'X'
    float current; // 电流 (A)
    float voltage; // 电压 (V)
    float power;   // 功率 (W)
    char end;      // 帧尾 'Y'
    uint8_t reserve[5]; // 预留5字节
} frame_t;
#pragma pack(pop) // pop:恢复保存的对齐方式

void CommunicateTask(void const * argument);

#endif //POWERMETER_Y_UART_H