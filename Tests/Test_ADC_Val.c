
#include "BSP_CAN.h"
#include "config.h"
#include "common.h"
#include "BSP_ADC.h"

/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define BSPVARIABLE 0x10b
 
int main(void){
    BSP_ADC_Init();
    
    while(1){
            
        
            volatile int32_t test = BSP_ADC_UpdateMeasurements();
            //Convert from 0-3300 mv range to 0-14000 mv range
            //printf("mV reading after ADC converstion: %ld\n\r", test);
            volatile int32_t orig_mv = (3254000-test*1000) / 220;
            //printf("Original voltage in mV: %ld\n\r", orig_mv);
        }
}