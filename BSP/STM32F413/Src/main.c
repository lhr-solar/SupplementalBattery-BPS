 /* Program for UTSVT BeVolt's Battery Protection System*/
 
#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC"
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define BSPVARIABLE 0x10b
 
int main(void){
    while(checkVoltage() >= 0){
        while(true){
        BSP_CAN_Write(BSPVARIABLE, checkVoltage());     //send message to CAN Controller 
    }
}