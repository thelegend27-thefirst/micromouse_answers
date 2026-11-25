#pragma once

#ifndef ADC1_H
#define ADC1_H

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void ADC1_Init(void);

bool ADC1_Read(uint8_t channel, uint16_t *value);

#ifdef __cplusplus
}
#endif

#endif