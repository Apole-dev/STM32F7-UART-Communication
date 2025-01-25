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

//Register offsets
#define GPIO_MODER_OFFSET   0x00
#define GPIO_PUPDR_OFFSET   0x0C
#define GPIO_IDR_OFFSET     0x10
#define GPIO_ODR_OFFSET     0x14



#define GPIO_MODER(port) (*(volatile uint32_t*)(port + GPIO_MODER_OFFSET))
#define GPIO_ODR(port)   (*(volatile uint32_t*)(port + GPIO_ODR_OFFSET))



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

    if(myConfig->channelFrequency < 410 || myConfig->channelFrequency > 432) return;
    uint8_t channelCommand = 0;
    channelCommand |= ((myConfig->channelFrequency - 410) << 0); // 0-1-2-3-4
    command[4] = channelCommand;

    uint8_t optionCommand = 0;
    optionCommand |= (myConfig->transmissionPower << 0); // 0-1
    optionCommand |= (myConfig->enableFEC << 2);        // 2
    optionCommand |= (myConfig->wirlessWakeUpTime << 3); // 3-4-5
    optionCommand |= (myConfig->ioDriveModeEnable << 6); // 6
    optionCommand |= (myConfig->fixedTransmissionEnable << 7); // 7
    command[5] = optionCommand;



}

void LoRa_ReciveResponse(LoRa_Command_Setup* myConfig){

}

void LoRa_ModeSet(LoRa_Mode* mode,uint16_t port,uint16_t M0,uint16_t M1){

    switch (*mode) {
        case NORMAL:            // M0-M1 0-0
            GPIO_MODER(port) |=  (1 << M0*2);
            GPIO_MODER(port) |=  (1 << M1*2);
            GPIO_ODR(port)   &= ~(1 << M0);
            GPIO_ODR(port)   &= ~(1 << M1);
        case WAKE_UP:           // M0-M1 1-0
            GPIO_MODER(port) |=  (1 << M0*2);
            GPIO_MODER(port) |=  (1 << M1*2);
            GPIO_ODR(port)   |=  (1 << M0);
            GPIO_ODR(port)   &= ~(1 << M1);
        case POWER_SAVING:      // M0-M1 0-1
            GPIO_MODER(port) |=  (1 << M0*2);
            GPIO_MODER(port) |=  (1 << M1*2);
            GPIO_ODR(port)   &=  (1 << M0);
            GPIO_ODR(port)   |=  (1 << M1);
        case SLEEP:             // M0-M1 1-1
            GPIO_MODER(port) |=  (1 << M0*2);
            GPIO_MODER(port) |=  (1 << M1*2);
            GPIO_ODR(port)   |=  (1 << M0);
            GPIO_ODR(port)   |=  (1 << M1);
    }
}

bool LoRa_ReadOperatingParams(LoRa_Mode* currentMode,LoRa_Command_Setup* myConfig){

    if (*currentMode != SLEEP & myConfig->baudRate == BAURD_RATE_9600 & myConfig->pairityState == PAIRITY_NONE)
        return false;

    return true;
}

bool LoRa_ReadVersionNumber(LoRa_Mode* currentMode, LoRa_Command_Setup* myConfig){

    if (*currentMode != SLEEP & myConfig->baudRate == BAURD_RATE_9600 & myConfig->pairityState == PAIRITY_NONE)
        return false;

    return true;
}

bool LoRa_Reset(LoRa_Mode* currentMode,LoRa_Command_Setup* myConfig){

    if (*currentMode != SLEEP & myConfig->baudRate == BAURD_RATE_9600 & myConfig->pairityState == PAIRITY_NONE)
        return false;

    return true;
}


