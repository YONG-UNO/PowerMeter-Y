//
// Created by DingYong on 2026/3/12.
//
#ifndef POWERMETER_Y_INA226_H
#define POWERMETER_Y_INA226_H

#include <stdint.h>


#define INA226_IIC_ADD (0x40<<1) // A0,A1 to GND -> addr 1000000

#define CONFIGURATION_REGISTER 0x00 // config register RW
#define SHUNT_VOLTAGE_REGISTER 0x01 // shunt voltage register(读取分流电阻两端电压) R
#define BUS_VOLTAGE_REGISTER 0x02 // 读取总线电压 R
#define POWER_REGISTER 0x03 // 读取计算后的功率值 R
#define CURRENT_REGISTER 0x04 // 读取计算后的电流值 R
#define CALIBRATION_REGISTER 0x05 // 1.配置报警条件(过流,过压,欠压) 2.查看adc转化完成状态 3. 使能/失能报警引脚输出 RW
#define ALERT_LIMIT_REGISTER 0x06 // 报警阈值设置 RW
#define MANUFACTURER_ID_REGISTER 0xFE // 芯片厂商ID 固定值 5449h（二进制 01010100 01001001），用于验证芯片真伪 / 型号 R
#define DIE_ID_REGISTER 0xFF // 芯片唯一编号 R

uint8_t Check(void);


#endif //POWERMETER_Y_INA226_H