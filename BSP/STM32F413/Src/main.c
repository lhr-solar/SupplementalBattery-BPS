 /* Program for UTSVT BeVolt's Battery Protection System*/
 
#include "BSP_CAN.h"
#include "config.h"

/* Copyright (c) 2020 UT Longhorn Racing Solar */

#define BSPVARIABLE "0x10b"
// #include "ALEX FOLDER " ==> will hold checkVoltage() function

int main(void){
   // while(checkVolatge() >= 0){
        while(true){
        BSP_CAN_Write(BSPVARIABLE, checkVoltage());     //send message to CAN Controller 
    }
}