#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "common.h"
#include "stm32f4xx_adc.h"
#include "config.h"
#include "stm32f4xx.h"

//Initialize ADC
void BSP_ADC_Init();

//Return value of ADC measurements in mV
int32_t BSP_ADC_UpdateMeasurements(void);

#endif