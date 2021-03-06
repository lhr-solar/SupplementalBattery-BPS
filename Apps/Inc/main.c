/* Copyright (c) 2020 UT Longhorn Racing Solar */

#include "BSP_CAN.h"
#include "config.h"
// #include "ALEX FOLDER " ==> will hold checkVoltage() function

int main(void){
    while(checkVolatge() > 0){
        BSP_CAN_Write(0x10B, checkVoltage() )     //send message to CAN Controller 
    }
}
        


