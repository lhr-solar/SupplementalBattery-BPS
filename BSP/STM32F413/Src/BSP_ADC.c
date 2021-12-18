 /* Program for UTSVT BeVolt's Battery Protection System*/
 /* Copyright (c) 2021 UT Longhorn Racing Solar */
#include "BSP_ADC.h"

/**
 * @brief   Initializes the ADC module for use with the rest of the electrical system.
 * @param   None
 * @return  None
 */
void BSP_ADC_Init(){
	ADC_CommonInitTypeDef ADC_CommonStruct;
	ADC_InitTypeDef ADC_InitStruct;	
	GPIO_InitTypeDef GPIO_InitStruct;

	/* ADC configuration **************************************************/

	/* Enable ADC clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 

	/* ADC Common Initialization */
	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonStruct);

	/* ADC Struct Initialization, Set up DMA to use multiple channels */ 
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;	
	ADC_InitStruct.ADC_ScanConvMode = ENABLE; 
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; 
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = 1; 
	ADC_Init(ADC1, &ADC_InitStruct);

	/* ADC GPIO configuration **************************************************/

	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

	/* Connect PA0 to ADC */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; 
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOA,&GPIO_InitStruct);


	/* Channel configuration */
	// Apparently channel 2 has priority, or is at least read first.
	// If you change the priorities, be prepared to have the order in the array change.
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);

	// Enable ADC1
	ADC_Cmd(ADC1, ENABLE);

	ADC_SoftwareStartConv(ADC1);
}

/**
 * @brief   Converts an analog reading from 0-14 V to a digital value from 0-4095. Converts this digital reading into mV from 0-14,000 to prevent data loss.
 * @param   None
 * @return  A voltage reading from 0-14,000 mV
 */
int32_t BSP_ADC_UpdateMeasurements(void){
    uint16_t val = ADC_GetConversionValue(ADC1); 
    int32_t mV = (val * 3300)/4095;
    return mV;
} 