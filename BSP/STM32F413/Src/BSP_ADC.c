 /* Program for UTSVT BeVolt's Battery Protection System*/
 /* Copyright (c) 2021 UT Longhorn Racing Solar */
#include "BSP_ADC.h"

void BSP_ADC_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable the ADC clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); // Enable the PA clock

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; // Using pins PA0 for the ADC
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN; // Analog Input
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; // High impedence
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	// ADC Common Init
	ADC_CommonInitTypeDef ADC_CommonStruct;
	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonStruct);

	// Set up to use DMA so that multiple channels can be used
	ADC_InitTypeDef ADC_InitStruct;	// Initialization structure
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;	// High resolution
	ADC_InitStruct.ADC_ScanConvMode = ENABLE; // So we can go through all the channels
	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; // Cycle the channels
	ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = 1; // We have two channels that we need to read

	ADC_Init(ADC1, &ADC_InitStruct);

	// Configure the channels
	// Apparently channel 2 has priority, or is at least read first.
	// If you change the priorities, be prepared to have the order in the array change.
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_480Cycles);

	// Enable ADC1
	ADC_Cmd(ADC1, ENABLE);

	ADC_SoftwareStartConv(ADC1);
}

float BSP_ADC_UpdateMeasurements(void){
    uint16_t val = ADC_GetConversionValue(ADC1); //0 means 14V and 1 means 0V
    float voltage;
    val = 1 - val;
    voltage = val * 14;
    return voltage;
}