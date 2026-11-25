#pragma once 
#include "main.h"
#include "gpio.hpp"
#include "adc1.h"
#include "delay_us.h"

uint16_t IR_Read(GPIO& led, uint32_t channel);