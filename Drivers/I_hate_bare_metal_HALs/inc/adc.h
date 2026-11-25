#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

void MX_ADC1_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
