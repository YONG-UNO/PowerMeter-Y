//
// Created by DingYong on 2026/3/12.
//

#include "INA226.h"
#include <stdint.h>
#include "i2c.h"
#include "stm32f1xx_hal_i2c.h"

static uint8_t Write(I2C_HandleTypeDef *hi2c, uint8_t reg, uint16_t data);
static uint16_t Read(I2C_HandleTypeDef *hi2c, uint8_t reg);

uint8_t Check(void) {
    uint16_t manufacture_id = Read(&hi2c1, MANUFACTURER_ID_REGISTER);
    uint16_t die_id = Read(&hi2c1, DIE_ID_REGISTER);

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

// read register result
static uint16_t Read(I2C_HandleTypeDef *hi2c, uint8_t reg) {
    uint8_t buf[2] = {0};
    uint16_t result = 0;

     // step 1: send register address
    if (HAL_I2C_Master_Transmit(hi2c, INA226_IIC_ADD, &reg, 1, 100) != HAL_OK) {
        return 0; // error
    }
    if (HAL_I2C_Master_Receive(hi2c, INA226_IIC_ADD, buf, 2, 100) == HAL_OK) {
        result = (uint16_t)buf[0] << 8 | (uint16_t)buf[1];
    }

    return result;
}

// 总线电压
float BusVoltage(void) {
    static uint16_t result = 0;
    result = Read(&hi2c1, BUS_VOLTAGE_REGISTER);
    return (float)result * 1.25f / 1000.0f;
}

// 分流电阻电压
float ShuntVoltage(void) {
    uint16_t result = Read(&hi2c1, SHUNT_VOLTAGE_REGISTER);
    return (float)result * 2.5f / 1000000.0f;
}

uint8_t calibration_flag = 0;

// 读取电流 (A)
float Current(void) {

    if (calibration_flag == 0) {
        Write(&hi2c1, CALIBRATION_REGISTER, (uint16_t)CALIBRATION_VALUE);
        calibration_flag = 1;
    }

    int16_t result = (int16_t)Read(&hi2c1, CURRENT_REGISTER);
    return (float)result * CURRENT_LSB;
}

// 读取功率 (W)
float Power(void) {

    if (calibration_flag == 0) {
        Write(&hi2c1, CALIBRATION_REGISTER, (uint16_t)CALIBRATION_VALUE);
        calibration_flag = 1;
    }

    uint16_t result = Read(&hi2c1, POWER_REGISTER);
    return (float)result * POWER_LSB;
}