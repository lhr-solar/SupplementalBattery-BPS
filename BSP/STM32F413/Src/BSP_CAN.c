/* Copyright (c) 2020 UT Longhorn Racing Solar */

#include "BSP_CAN.h"
#include "stm32f4xx.h"

#define CAN_MODE        CAN_Mode_Normal

static CanTxMsg TxMessage;
static CanRxMsg RxMessage;

static bool RxFlag = false;

static void floatTo4Bytes(uint8_t val, uint8_t bytes_array[4]);

/**
 * @brief   Initializes the CAN module that communicates with the rest of the electrical system.
 * @param   None
 * @return  None
 */
void BSP_CAN_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;

    /* CAN GPIOs configuration **************************************************/

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* Connect CAN pins to AF9 */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF8_CAN1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF8_CAN1); 

    /* Configure CAN RX and TX pins */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* CAN configuration ********************************************************/  
    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /* CAN register init */
    //CAN_DeInit(CAN1);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_MODE;
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;

    /* CAN Baudrate = 125 KBps
        * 1/(prescalar + (prescalar*(BS1+1)) + (prescalar*(BS2+1))) * Clk = CAN Baudrate
        * The AHB1 clk which drives CAN seems to be set to around 20MHz, but this should be verified.
    */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq; 
    CAN_InitStructure.CAN_Prescaler = 16;
    CAN_Init(CAN1, &CAN_InitStructure);

    /* CAN filter init */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(CAN1, &CAN_FilterInitStructure);

    /* Transmit Structure preparation */
    TxMessage.ExtId = 0x1;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* Receive Structure preparation */
    RxMessage.StdId = 0x00;
    RxMessage.ExtId = 0x00;
    RxMessage.IDE = CAN_ID_STD;
    RxMessage.DLC = 0;
    RxMessage.FMI = 0;

    /* Enable FIFO 0 message pending Interrupt */
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

    // Enable Rx interrupts
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
}

/**
 * @brief   Transmits the data onto the CAN bus with the specified id
* @param   id : Message of ID. Also indicates the priority of message. The lower the value, the higher the priority.
* @param   Voltage : the voltage value at that moment in a float
* @return  0 if module was unable to transmit the data onto the CAN bus. Any other value indicates data was transmitted.
 */
uint8_t BSP_CAN_Write(uint32_t id, float Voltage) {
    
    TxMessage.StdId = id;
    floatTo4Bytes(Voltage, &TxMessage.Data[4]);

	return CAN_Transmit(CAN1, &TxMessage);
}

/**
 * @brief   Gets the data that was received from the CAN bus.
 * @note    Non-blocking statement
 * @pre     The data parameter must be at least 8 bytes or hardfault may occur.
 * @param   id : pointer to store id of the message that was received.
 * @param   data : pointer to store data that was received. Must be 8bytes or bigger.
 * @return  0 if nothing was received so ignore id and data that was received. Any other value indicates data was received and stored.
 */
uint8_t BSP_CAN_Read(uint32_t *id, uint8_t *data) {
    if(RxFlag){
		for(int i = 0; i < 8; i++){
			data[i] = RxMessage.Data[i];
		}
        *id = RxMessage.StdId;
		RxFlag = false;
		return 1;
	}
    return 0;
}

void CAN1_RX0_IRQHandler(void)
{
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);


    if ((RxMessage.StdId == 0x001)&&(RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1)){
        // TODO: do stuff
        RxFlag = true;
    }

}

static void floatTo4Bytes(uint8_t val, uint8_t bytes_array[4]) {
	uint8_t volt;
	// Create union of shared memory space
	union {
			float float_variable;
			uint8_t volt_array[4];
	} u;
	// Overite bytes of union with float variable
	u.float_variable = val;
	// Assign bytes to input array
	memcpy(bytes_array, u.volt_array, 4);
    volt = bytes_array[3];
	bytes_array[3] = bytes_array[0];
	bytes_array[0] =    volt;
    volt = bytes_array[2];
	bytes_array[2] = bytes_array[1];
	bytes_array[1] =    volt;	
}
