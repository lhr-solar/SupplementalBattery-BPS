
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define BSPVARIABLE 0x10b
 
int main(void){
    BSP_ADC_Init();
    BSP_CAN_Init();
    int err;
    while(1) {
        //send message to CAN Controller 
        err = BSP_CAN_Write(BSPVARIABLE, BSP_ADC_UpdateMeasurements());
        /*Use for loop, 1-5 hz, so 200ms to 1 second delay*/
        for (volatile int i=0; i<2000000; i++);

    }
}