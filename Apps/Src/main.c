
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
#include <string.h>
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define CAN_ID 0x10b //CAN ID
 
int main(void){
    BSP_ADC_Init();
    BSP_CAN_Init();

    // TODO: For debugging during integration. Remove later
    volatile uint8_t mailBoxNum; 
    volatile uint8_t errRead;    
    volatile uint8_t transmitState; 

    uint32_t rxId;
    uint8_t rxData[8];
    volatile int32_t batterymV;
    volatile uint8_t numMessagesWaiting;


    while(1) {
        batterymV = (3254000-BSP_ADC_UpdateMeasurements()* 1000)/220; 
        mailBoxNum = BSP_CAN_Write(CAN_ID, batterymV); //send mV reading from battery back to CAN
        
        // TODO: For debugging during integration. Remove later
        memset(rxData, 0, sizeof(rxData));
        errRead= BSP_CAN_Read(&rxId, rxData); 
        transmitState= CAN_TransmitStatus(CAN1, mailBoxNum); //0 for fail, 1 for good, 2 for pending
        numMessagesWaiting= CAN_MessagePending(CAN1, CAN_FIFO0); //see how many messages pending transmission
        volatile int test=0;

        //Experimentally determined delay of 1.5 seconds
        for (volatile int i=0; i<2000000; i++);
        
    }
}