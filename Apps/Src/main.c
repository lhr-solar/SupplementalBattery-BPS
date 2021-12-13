
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
#include <string.h>
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define CAN_ID 0x10b //CAN ID
 
int main(void){
    BSP_ADC_Init();
    BSP_CAN_Init();
    volatile uint8_t mailBoxNum;
    volatile uint8_t errRead;
    uint32_t rxId;
    uint8_t rxData[8];
    volatile int32_t batterymV;

    batterymV = (3254000-BSP_ADC_UpdateMeasurements()* 1000)/220; 
    mailBoxNum = BSP_CAN_Write(CAN_ID, batterymV); //send mV reading from battery back to CAN
    volatile uint8_t transmitStat= CAN_TransmitStatus(CAN1, mailBoxNum); //0 for fail, 1 for good, 2 for pending??

    while(1) {
        //send message to CAN Controller 
        //batterymV = (3254000-BSP_ADC_UpdateMeasurements()* 1000)/220; //this is op amp equation but reversed to get original battery voltage input
        //errWrite = BSP_CAN_Write(CAN_ID, batterymV); //send mV reading from battery back to CAN
        memset(rxData, 0, sizeof(rxData));
        errRead= BSP_CAN_Read(&rxId, rxData); //rxId and rxData should be same as what we wrote

        volatile int test=0;
        /*Use for loop, 1-5 hz, so 200ms to 1 second delay*/
        //for (volatile int i=0; i<2000000; i++);
        
    }
}