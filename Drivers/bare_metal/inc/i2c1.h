#pragma once

#include "main.h"
#include "stm32f411xe.h"
#include <stdint.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
@brief Initializes I2c
@param none
@return none
*/
void I2C1_Init(void);

/*
@brief write to peripheral
@param address
@param data
@param # of bytes
@return boolean
*/
bool I2C1_Write(uint8_t address, const uint8_t *data, uint16_t length);

/*
@brief read from peripheral
@param address
@param data
@param # of bytes
@return boolean
*/
bool I2C1_Read(uint8_t address, uint8_t *data, uint16_t length);

/*
@brief read for peripherals that are being difficult
@param address
@param register
@param data
@param # of bytes
@return boolean
*/
bool I2C1_ReadRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t length);


#ifdef __cplusplus
}
#endif

