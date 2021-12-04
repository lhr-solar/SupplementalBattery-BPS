
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define BSPVARIABLE 0x10b
 
int main(void){
    BSP_ADC_Init();
    while(1) {

        // Test: if we read a value from the ADC conversion in an acceptable range, light up pin
        //Look at DAC1?
        volatile int32_t test1 = BSP_ADC_UpdateMeasurements();

        //for (volatile int i=0; i<2000000; i++);

        //Convert from 0-3300 mv range to 0-14000 mv range
        volatile int32_t test2 = (3254000-test1 * 1000)/220; //this is op amp equation but reversed to get original battery voltage input

        volatile int32_t t=1;

    }
}