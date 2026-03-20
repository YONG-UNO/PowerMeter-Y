//
// Created by DingYong on 2026/3/12.
//

#include "INA226.h"

#include <stdint.h>

#include "i2c.h"
#include "stm32f1xx_hal_i2c.h"


static uint16_t Read(uint8_t reg);

 uint8_t Check(void) {
    uint16_t manufacture_id, die_id;
    manufacture_id = Read(MANUFACTURER_ID_REGISTER);
    die_id = Read(DIE_ID_REGISTER);

    if ((manufacture_id == 0x5449) && (die_id == 0x2260)) {
        return 0; // ok
    }

    return 1; //no ok
}

static uint8_t Write(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t data) {
     uint8_t buf[3];
     buf[0] = reg;  // register address
     buf[1] = (data >> 8) & 0xFF; // high 8 bits MSB
     buf[2] = data & 0xFF; // low 8 bits LSB

     if (HAL_I2C_Master_Transmit(hi2c, INA226_IIC_ADD, buf, 3, 100) == HAL_OK) {
         return 0;
     }
     return 1;
 }

static uint16_t Read(uint8_t reg) {
    uint8_t buf[2] = {0};
    uint16_t result = 0;

    if (HAL_I2C_Master_Transmit(&hi2c1, INA226_IIC_ADD, &reg, 1, 100) != HAL_OK) {
        return 0;
    }
    if (HAL_I2C_Master_Receive(&hi2c1, INA226_IIC_ADD, buf, 2, 100) == HAL_OK) {
        result = (uint16_t)buf[0] << 8 | (uint16_t)buf[1];
    }

    return result;
}


// #include "ina226.h"
//
// extern I2C_HandleTypeDef hi2c1; // 全局I2C句柄，CubeMX生成，按需替换hi2c2
//
// /**
//  * @brief  检测INA226是否在线（读厂商ID和芯片ID，最核心的通信验证）
//  * @retval 0-在线，1-不在线
//  */
// uint8_t INA226_Check(void)
// {
//     uint16_t mfr_id, die_id;
//     // 读厂商ID（固定0x5449）和芯片ID（固定0x2260）
//     mfr_id = INA226_ReadReg(INA226_REG_MFR_ID);
//     die_id = INA226_ReadReg(INA226_REG_DIE_ID);
//     // 验证ID是否正确
//     if((mfr_id == 0x5449) && (die_id == 0x2260))
//     {
//         return 0; // 通信正常，芯片在线
//     }
//     return 1; // 通信失败，芯片未检测到
// }
//
// /**
//  * @brief  向INA226指定寄存器写16位数据（MSB高位在前，符合手册要求）
//  * @param  reg: 寄存器地址
//  * @param  data: 要写入的16位数据
//  * @retval 0-成功，1-失败
//  */
// uint8_t INA226_WriteReg(uint8_t reg, uint16_t data)
// {
//     uint8_t buf[3];
//     buf[0] = reg;                // 寄存器地址
//     buf[1] = (data >> 8) & 0xFF; // 高8位（MSB）
//     buf[2] = data & 0xFF;        // 低8位（LSB）
//     // I2C主发送：地址+寄存器+16位数据，超时100ms
//     if(HAL_I2C_Master_Transmit(&hi2c1, INA226_I2C_ADDR, buf, 3, 100) == HAL_OK)
//     {
//         return 0;
//     }
//     return 1;
// }
//
// /**
//  * @brief  从INA226指定寄存器读16位数据（MSB高位在前，符合手册要求）
//  * @param  reg: 寄存器地址
//  * @retval 读取到的16位数据，通信失败返回0
//  */
// uint16_t INA226_ReadReg(uint8_t reg)
// {
//     uint8_t buf[2] = {0};
//     uint16_t res = 0;
//     // 第一步：发送寄存器地址，告诉INA226要读哪个寄存器
//     if(HAL_I2C_Master_Transmit(&hi2c1, INA226_I2C_ADDR, &reg, 1, 100) != HAL_OK)
//     {
//         return 0; // 地址发送失败
//     }
//     // 第二步：读取该寄存器的16位数据（高8位+低8位）
//     if(HAL_I2C_Master_Receive(&hi2c1, INA226_I2C_ADDR, buf, 2, 100) == HAL_OK)
//     {
//         res = (uint16_t)buf[0] << 8 | buf[1]; // 拼接高8位和低8位
//     }
//     return res;
// }


// read register result
static uint16_t RegisterRead(I2C_HandleTypeDef *hi2c, uint8_t reg) {
     uint8_t buf[2] = {0};
     uint16_t result = 0;

     // step 1: send register address
     if (HAL_I2C_Master_Transmit(hi2c, INA226_IIC_ADD, &reg, 1, 100) != HAL_OK) {
        return 0; // error
     }
     if (HAL_I2C_Master_Receive(hi2c, INA226_IIC_ADD, buf, 2, 100) == HAL_OK) {
         return 0;
     }

     return result;
 }


// read bus voltage
static float BusVoltage(I2C_HandleTypeDef *hi2c) {
     uint16_t result = RegisterRead(hi2c, BUS_VOLTAGE_REGISTER);
     return (float)result * 1.25f / 1000.0f;
 }