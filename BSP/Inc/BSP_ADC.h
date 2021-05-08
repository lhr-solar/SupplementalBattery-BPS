#include "common.h"
#include "stm32f4xx_adc.h"
#include "config.h"
#include "stm32f4xx.h"

//Initialize ADC
void BSP_ADC_Init();

//Return value of ADC measurements in mV
float BSP_ADC_UpdateMeasurements(void);