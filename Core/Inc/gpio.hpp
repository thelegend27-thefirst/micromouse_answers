#pragma once 
#include "main.h"
#include "gpio_driver.h"

class GPIO{
public:
    GPIO(GPIO_TypeDef* port, uint16_t pin);
        
    void HIGH();
    void LOW();
    void toggle();

private:
    GPIO_TypeDef* port;
    uint16_t pin;
};