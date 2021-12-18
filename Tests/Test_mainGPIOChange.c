//Test_mainGPIOChange.c


#include "BSP_CAN.h"
#include "config.h"
#include "BSP_ADC.h"
#include <string.h>
/* Copyright (c) 2021 UT Longhorn Racing Solar */

#define CAN_ID 0x10b //CAN ID
 
int main(void){
    //BSP_ADC_Init();
    //BSP_CAN_Init();
    volatile uint8_t mailBoxNum;
    volatile uint8_t errRead;
    volatile uint8_t transmitState;
    uint32_t rxId;
    uint8_t rxData[8];
    volatile int32_t batterymV;
    volatile uint8_t numMessagesWaiting;
    
    volatile int test=0;
    //initialize and configure pins B8 and B9 as GPIO output and toggle to see if anything shows
    GPIO_InitTypeDef GPIO_InitStructure;

   // (#) Enable the GPIO AHB clock using the following function
       RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

   //(#) Configure the GPIO pin(s) using GPIO_Init()
       //Four possible configuration are available for each pin:
       //(++) Output: Push-Pull (Pull-up, Pull-down or no Pull)
            //Open Drain (Pull-up, Pull-down or no Pull). In output mode, the speed 
            //is configurable: 2 MHz, 25 MHz, 50 MHz or 100 MHz.

    /* Configure pins 8 and 9 to toggle */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    //void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
    //{
  /* Check the parameters */
  //assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  //GPIOx->ODR ^= GPIO_Pin;}
while(1) {
        
        GPIO_ToggleBits(GPIOB, GPIO_Pin_8);
        GPIO_ToggleBits(GPIOB, GPIO_Pin_9);
        for (volatile int i=0; i<2000000; i++);
        volatile int test=0;
        
    }
}

