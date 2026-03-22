//
// Created by DingYong on 2026/3/12.
//
#ifndef POWERMETER_Y_INA226_H
#define POWERMETER_Y_INA226_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"


#define MAX_EXPECTED_CURRENT     15.0f // 最大预期电流 (A)
#define R_SHUNT                  0.001f // 分流电阻阻值 (Ω)，这里是1mΩ
#define CURRENT_LSB              (MAX_EXPECTED_CURRENT / 32768.0f) // 电流分辨率 (A/bit)
#define CALIBRATION_VALUE        170640//(0.00512f / (CURRENT_LSB * R_SHUNT)) // 校准值
#define POWER_LSB                (25 * CURRENT_LSB) // 功率分辨率 (W/bit)，手册规定为Current_LSB的25倍

#define INA226_IIC_ADD (0x40<<1)      // A0,A1 to GND -> addr 1000000
#define CONFIGURATION_REGISTER 0x00   // config register RW
#define SHUNT_VOLTAGE_REGISTER 0x01   // shunt voltage register(读取分流电阻两端电压) R
#define BUS_VOLTAGE_REGISTER 0x02     // 读取总线电压 R
#define POWER_REGISTER 0x03           // 读取计算后的功率值 R
#define CURRENT_REGISTER 0x04         // 读取计算后的电流值 R
#define CALIBRATION_REGISTER 0x05     // 1.配置报警条件(过流,过压,欠压) 2.查看adc转化完成状态 3. 使能/失能报警引脚输出 RW
#define ALERT_LIMIT_REGISTER 0x06     // 报警阈值设置 RW
#define MANUFACTURER_ID_REGISTER 0xFE // 芯片厂商ID 固定值 5449h（二进制 01010100 01001001），用于验证芯片真伪 / 型号 R
#define DIE_ID_REGISTER 0xFF          // 芯片唯一编号 R

uint8_t Check(void);       // 检测INA226是否在线
float BusVoltage(void);    // 读取总线电压 (V)
float ShuntVoltage(void);  // 读取分流电压 (mV)
float Current(void);       // 读取电流 (A)
float Power(void);         // 读取功率 (W)

#endif //POWERMETER_Y_INA226_H