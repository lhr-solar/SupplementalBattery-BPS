
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
#include <string.h>
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define CAN_ID 0x10b //CAN ID
 
int main(void){
    BSP_ADC_Init();
    BSP_CAN_Init();

    int16_t batterymV;

    while(1) {
        batterymV = (3254000-BSP_ADC_UpdateMeasurements()* 1000)/220; 
        BSP_CAN_Write(CAN_ID, batterymV); //send mV reading from battery back to CAN

        //Experimentally determined delay of 1.5 seconds
        for (volatile int i=0; i<2000000; i++);
        
    }
}