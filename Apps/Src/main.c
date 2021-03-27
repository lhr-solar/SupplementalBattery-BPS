/* Copyright (c) 2020 UT Longhorn Racing Solar */

/** main.c
 * Program for UTSVT BeVolt's Battery Protection System
 */

/* Copyright (c) 2020 UT Longhorn Racing Solar */

#include "BSP_CAN.h"
#include "config.h"

int main(void){
    while(checkVolatge() > 0){
        BSP_CAN_Write(0x10B, checkVoltage());     //send message to CAN Controller 
    }
}
        


