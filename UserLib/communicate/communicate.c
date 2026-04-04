//
// Created by DingYong on 2026/3/21.
//

#include "communicate.h"

#include <string.h>

#include "../INA226/INA226.h"
#include "cmsis_os.h"
#include "usart.h"

static void PackageFrame(frame_t * frame);

static void PackageFrame(frame_t * frame) {
    frame->start = 'X';
    frame->end = 'Y';
    frame->current = Current();    // 读取INA226电流
    frame->voltage = BusVoltage(); // 读取总线电压
    frame->power = Power();        // 读取功率
    memset(frame->reserve, 0x00, 5); // 预留位填充0
}

void CommunicateTask(void const * argument) {
    (void) argument;

    static frame_t data;

    for (;;) {
        PackageFrame(&data); // 打包数据
        HAL_UART_Transmit_DMA(&huart3, (uint8_t *)&data, sizeof(frame_t));

        osDelay(2);
    }

}