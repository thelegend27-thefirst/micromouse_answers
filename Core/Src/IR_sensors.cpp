#include "IR_sensors.hpp"


uint16_t IR_Read(GPIO& led, uint32_t channel){
    
    led.LOW();
    delay_us(50);

    uint16_t ambient = 0;
    uint16_t reflected = 0;

    if (ADC1_Read(channel, &ambient) == 0){
        Error_Handler();
    }

    led.HIGH();
    delay_us(50);

    if (ADC1_Read(channel, &reflected) == 0){
        Error_Handler();
    }

    led.LOW();

    return (reflected > ambient)
           ? reflected - ambient
           : 0;
}