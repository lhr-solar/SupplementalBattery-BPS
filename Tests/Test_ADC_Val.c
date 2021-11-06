
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define BSPVARIABLE 0x10b
 
int main(void){
    BSP_ADC_Init();
    while(1) {

        // Test: if we read a value from the ADC conversion in an acceptable range, light up pin
        int32_t test = BSP_ADC_UpdateMeasurements();
        //Convert from 0-3300 mv range to 0-14000 mv range
        test = test * (1400/3300);
        //Somehow read test value. Should approximate input voltage
        /*Use for loop, 1-5 hz, so 200ms to 1 second delay*/
        for (volatile int i=0; i<2000000; i++);

    }
}