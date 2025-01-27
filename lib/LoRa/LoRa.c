/*
 * Documents: 
 *      https://www.st.com/resource/en/reference_manual/rm0431-stm32f72xxx-and-stm32f73xxx-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
 *      https://www.rcscomponents.kiev.ua/datasheets/e32-433t30d_usermanual_en_v1_6.pdf
 *
 * */

#include "LoRa_config.h"
#include <stdbool.h>
#include <stdint.h>
//#include "LoRa.h"

// GPIO Register offsets
#define GPIO_MODER_OFFSET   0x00
#define GPIO_PUPDR_OFFSET   0x0C
#define GPIO_IDR_OFFSET     0x10
#define GPIO_ODR_OFFSET     0x14

// USART Register offsets
#define USART_CR1_OFFSET           0x00
#define USART_BRR_OFFSET           0x0C
#define USART_ISR_OFFSET           0x1C
#define USART_RDR_OFFSET           0x24
#define USART_TDR_OFFSET           0x28

// Frequency range validation
#define LORA_MIN_FREQ 410
#define LORA_MAX_FREQ 432


// GPIO MACRO Funcion
#define GPIO_MODER(port) (*(volatile uint32_t*)(port + GPIO_MODER_OFFSET))
#define GPIO_ODR(port)   (*(volatile uint32_t*)(port + GPIO_ODR_OFFSET))

// USART MACRO Funcion
#define USART_CR1(port) (*(volatile uint32_t*)(port + USART_CR1_OFFSET))
#define USART_BRR(port) (*(volatile uint32_t*)(port + USART_BRR_OFFSET))
#define USART_ISR(port) (*(volatile uint32_t*)(port + USART_ISR_OFFSET))
#define USART_RDR(port) (*(volatile uint32_t*)(port + USART_RDR_OFFSET))
#define USART_TDR(port) (*(volatile uint32_t*)(port + USART_TDR_OFFSET))


void LoRa_INIT(){

}

void LoRa_SendCommand(LoRa_Command_Setup* myConfig){
    uint8_t command[6];

    command[0] = myConfig->paramState;
    command[1] = myConfig->HIGH_ADRESS_CODE;
    command[2] = myConfig->LOW_ADRESS_CODE;

    uint8_t speedCommand = 0;
    speedCommand |= (myConfig->airDataRate << 0);   // 0-1-2
    speedCommand |= (myConfig->baudRate << 3);      // 3-4-5
    speedCommand |= (myConfig->pairityState << 6);  // 6-7-8
    command[3] = speedCommand;

    if(myConfig->channelFrequency <= 410 || myConfig->channelFrequency >= 432) return;
    uint8_t channelCommand = 0;
    channelCommand |= ((myConfig->channelFrequency - LORA_MIN_FREQ) << 0); // 0-1-2-3-4
    command[4] = channelCommand;

    uint8_t optionCommand = 0;
    optionCommand |= (myConfig->transmissionPower << 0); // 0-1
    optionCommand |= (myConfig->enableFEC << 2);        // 2
    optionCommand |= (myConfig->wirlessWakeUpTime << 3); // 3-4-5
    optionCommand |= (myConfig->ioDriveModeEnable << 6); // 6
    optionCommand |= (myConfig->fixedTransmissionEnable << 7); // 7
    command[5] = optionCommand;



}

void LoRa_ReciveResponse(LoRa_Configs* myConfig,uint8_t* response ){
    
    if (!response) return ;
    // uint8_t response[6]; //Alternate option

    //USART->ISR RXNE(: Read data register not empty) BIT 5
    //Wait until data arrive

    for (int8_t i=0; i<6; i++) {
        while (!(USART_ISR(myConfig->USART_PIN) & (1 << 5))); // Wait for RXNE flag
        response[i] =USART_RDR(myConfig->USART_PIN);
    }
}

void LoRa_ModeSet(LoRa_Mode* mode,LoRa_Configs* myConfig){

    /* 
     * FIX: CLEAR THE OUTPUTS BEFORE SET 
     */

    switch (*mode) {
        case NORMAL:            // M0-M1 0-0
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M0*2);
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M1*2);
            GPIO_ODR(myConfig->GPIO_PORT)   &= ~(1 << myConfig->M0);
            GPIO_ODR(myConfig->GPIO_PORT)   &= ~(1 << myConfig->M1);
            break;

        case WAKE_UP:           // M0-M1 1-0
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M0*2);
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M1*2);
            GPIO_ODR(myConfig->GPIO_PORT)   |=  (1 << myConfig->M0);
            GPIO_ODR(myConfig->GPIO_PORT)   &= ~(1 << myConfig->M1);
            break;

        case POWER_SAVING:      // M0-M1 0-1
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M0*2);
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M1*2);
            GPIO_ODR(myConfig->GPIO_PORT)   &= ~(1 << myConfig->M0);
            GPIO_ODR(myConfig->GPIO_PORT)   |=  (1 << myConfig->M1);
            break;

        case SLEEP:             // M0-M1 1-1
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M0*2);
            GPIO_MODER(myConfig->GPIO_PORT) |=  (1 << myConfig->M1*2);
            GPIO_ODR(myConfig->GPIO_PORT)   |=  (1 << myConfig->M0);
            GPIO_ODR(myConfig->GPIO_PORT)   |=  (1 << myConfig->M1);
            break;
    }
}



bool LoRa_ReadOperatingParams(LoRa_Mode* currentMode,LoRa_Command_Setup* myCommand,LoRa_Configs* myConfig,uint8_t* response){

    // Validate parameters and mode
    if (!currentMode || !myCommand || !myConfig || !response ||
        *currentMode != SLEEP ||
        myCommand->baudRate != BAURD_RATE_9600 ||
        myCommand->pairityState != PAIRITY_NONE) {
        return false;
    }


    return true;
}

bool LoRa_ReadVersionNumber(LoRa_Mode* currentMode, LoRa_Command_Setup* myCommand,LoRa_Configs* myConfig,uint8_t* response){

    // Validate parameters and mode
    if (!currentMode || !myCommand || !myConfig || !response ||
        *currentMode != SLEEP ||
        myCommand->baudRate != BAURD_RATE_9600 ||
        myCommand->pairityState != PAIRITY_NONE) {
        return false;
    }

    for (uint8_t i=0; i<3 i++) {
        USART_TDR(myConfig->USART_PIN) = LORA_READ_VERSION;
    }
    
    // TODO: ADD DELAY TO GET RIGHT RESPONSE NOT SURE!  
    LoRa_ReciveResponse(myConfig,response);

    return true;
}

bool LoRa_Reset(LoRa_Mode* currentMode,LoRa_Command_Setup* myCommand,LoRa_Configs* myConfig,uint8_t* response){

    // Validate parameters and mode
    if (!currentMode || !myCommand || !myConfig || !response ||
        *currentMode != SLEEP ||
        myCommand->baudRate != BAURD_RATE_9600 ||
        myCommand->pairityState != PAIRITY_NONE) {
        return false;
    }


    return true;
}


