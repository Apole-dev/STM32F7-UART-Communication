/*
 * Documentation :  https://www.rcscomponents.kiev.ua/datasheets/e32-433t30d_usermanual_en_v1_6.pdf
 * Section       :  6.Operating Mode & 7.Command Format
 *
*/


#ifndef LORA_CONFIG
#define LORA_CONFIG


#include <stdint.h>
#include <stdbool.h>
#include "LoRa_enums.h"

const uint8_t LORA_READ_PARAM   = 0xC1 ;
const uint8_t LORA_READ_VERSION = 0xC3;
const uint8_t LORA_RESET        = 0xC4;

typedef enum{
    NORMAL,
    WAKE_UP,
    POWER_SAVING,
    SLEEP
}LoRa_Mode;

typedef struct {

    //PINOUTS
    uint8_t M0_PIN;
    uint8_t M1_PIN;
    uint8_t AUX_PIN;
    uint8_t RX_PIN;
    uint8_t TX_PIN;

    //COMMAND SECTION

    bool saveParameters;
    uint16_t address;

    enum PARITY_STATE pairty;
    enum BAUD_RATE baudRate;
    enum AIR_DATA_RATE airDataRate;
    uint8_t channelFrequency;
    bool fixedTransmissionEnable;
    bool IODriveModeEnable;
    enum WIRLESS_WAKE_TIME wirlessWakeUpTime;
    bool FECEnable;
    enum TRANSMISSION_POWER transmisionPower;

 
}LoraConfig;

void LoRa_INIT();
void LoRa_SendCommand();
void LoRa_ModeSet(LoraConfig*,LoRa_Mode);
bool LoRa_ReadOperatingParams(uint32_t* response);
bool LoRa_ReadVersionNumber(uint32_t* response);
bool LoRa_Reset(LoraConfig*);

#endif // !LORA_CONFIG
