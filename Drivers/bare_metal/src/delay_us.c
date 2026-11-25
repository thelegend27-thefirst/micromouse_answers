#include "stm32f411xe.h"

void Delay_US_Init(void)
{
    // Enable DWT tracing
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // Reset cycle counter
    DWT->CYCCNT = 0;

    // Start cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000U);

    while ((uint32_t)(DWT->CYCCNT - start) < cycles)
    {
        // Busy wait
    }
}