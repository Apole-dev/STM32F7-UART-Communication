#ifndef LORA_ENUMS
#define LORA_ENUMS

#include <stdbool.h>
#include <stdint.h>
typedef struct {

    //PINOUTS
    uint8_t M0_PIN;
    uint8_t M1_PIN;
    uint8_t AUX_PIN;
    uint8_t RX_PIN;
    uint8_t TX_PIN;

    //MODE
    

    //COMMAND SECTION

    bool saveParameters;
    uint16_t address;

    /*
    PARITY_STATE pairty;
    BAUD_RATE baudRate;
    AIR_DATA_RATE airDataRate;
    uint8_t channelFrequency;
    bool fixedTransmissionEnable;
    bool IODriveModeEnable;
    WIRLESS_WAKE_TIME wirlessWakeUpTime;
    bool FECEnable;
    TRANSMISSION_POWER transmisionPower;
    */

 
}LoraConfig;



#endif // !LORA_ENUMS
