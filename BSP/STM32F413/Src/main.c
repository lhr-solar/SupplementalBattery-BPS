 /* Program for UTSVT BeVolt's Battery Protection System*/
 
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
        err = BSP_CAN_Write(BSPVARIABLE, BSP_ADC_UpdateMeasurements()); //send message to CAN Controller 
        if (err == 0){/*ERROR HANDLING HERE*/}
    }
}