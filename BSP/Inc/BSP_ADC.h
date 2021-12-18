#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "common.h"
#include "stm32f4xx_adc.h"
#include "config.h"
#include "stm32f4xx.h"

/**
 * @brief   Initializes the ADC module for use with the rest of the electrical system.
 * @param   None
 * @return  None
 */
void BSP_ADC_Init();


/**
 * @brief   Converts an analog reading from 0-14 V to a digital value from 0-4095. Converts this digital reading into mV from 0-14,000 to prevent data loss.
 * @param   None
 * @return  A voltage reading from 0-14,000 mV
 */
int32_t BSP_ADC_UpdateMeasurements(void);

#endif