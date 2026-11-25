#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

void Delay_US_Init(void);

void delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif
