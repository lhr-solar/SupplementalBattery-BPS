 /* Program for UTSVT BeVolt's Battery Protection System*/

#include "BSP_CAN.h"
#include "config.h"

/* Copyright (c) 2021 UT Longhorn Racing Solar */

int checkVoltage(void){
    ADC_VBATCmd(PA0, ENABLE);
}