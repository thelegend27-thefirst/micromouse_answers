
#include "adc1.h"

#define ADC1_TIMEOUT 200000U

void ADC1_Init(void)
{
    // Enable GPIOA, GPIOC and ADC1 clocks
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN |
                    RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    (void)RCC->APB2ENR;

    // Configure PA4, PA6, PA7 as analog inputs
    GPIOA->MODER |= 0x0000F300U;

    // Configure PC0 as analog input
    GPIOC->MODER |= 0x00000003U;

    // Disable internal pull-up/pull-down
    GPIOA->PUPDR &= ~0x0000F300U;
    GPIOC->PUPDR &= ~0x00000003U;

    // Disable ADC before configuration
    ADC1->CR2 &= ~ADC_CR2_ADON;

    // ADC clock = PCLK2 / 4
    ADC->CCR &= ~0x00030000U;
    ADC->CCR |=  0x00010000U;

    // 12-bit, single conversion, no DMA
    ADC1->CR1 = 0x00000000U;
    ADC1->CR2 = 0x00000000U;

    // One conversion in regular sequence
    ADC1->SQR1 = 0x00000000U;
    ADC1->SQR2 = 0x00000000U;
    ADC1->SQR3 = 0x00000000U;

    // 56 sampling cycles for channels 10, 4, 6, 7
    ADC1->SMPR1 &= ~0x00000007U;
    ADC1->SMPR1 |=  0x00000003U;

    ADC1->SMPR2 &= ~0x00FC7000U;
    ADC1->SMPR2 |=  0x006C3000U;

    // Clear status flags
    ADC1->SR = 0x00000000U;

    // Enable ADC
    ADC1->CR2 |= ADC_CR2_ADON;

    // ADC stabilization delay
    for (volatile uint32_t i = 0; i < 1000U; i++)
    {
        __NOP();
    }
}

bool ADC1_Read(uint8_t channel, uint16_t *value)
{
    if (value == 0)
        return false;

    // Only allow the four IR sensor channels
    if (channel != 10U && channel != 4U &&
        channel != 6U && channel != 7U)
        return false;

    // Select ADC channel
    ADC1->SQR3 = (uint32_t)channel;

    // Clear previous conversion flags
    ADC1->SR = 0x00000000U;

    // Start conversion
    ADC1->CR2 |= ADC_CR2_SWSTART;

    uint32_t timeout = ADC1_TIMEOUT;

    // Wait for conversion to finish
    while ((ADC1->SR & ADC_SR_EOC) == 0U)
    {
        if (timeout-- == 0U)
            return false;
    }

    // Read 12-bit ADC result
    *value = (uint16_t)(ADC1->DR & 0x0FFFU);

    return true;
}
