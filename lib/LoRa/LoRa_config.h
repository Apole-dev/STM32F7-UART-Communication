/*
 * Documentation :  https://www.rcscomponents.kiev.ua/datasheets/e32-433t30d_usermanual_en_v1_6.pdf
 * Section       :  6.Operating Mode & 7.Command Format
 *
*/


#ifndef LORA_CONFIG
#define LORA_CONFIG


#include <stdint.h>
#include <stdbool.h>


const uint8_t LORA_READ_PARAM   = 0xC1 ;
const uint8_t LORA_READ_VERSION = 0xC3;
const uint8_t LORA_RESET        = 0xC4;

typedef enum{
    NORMAL,
    WAKE_UP,
    POWER_SAVING,
    SLEEP
}LoRa_Mode;

typedef enum {
    SAVE_PARAM = 0xC0,
    
    DO_NOT_SAVE_PARAM = 0xC2,


    PAIRITY_NONE = 0,   // 0-0 
    PAIRITY_ODD  = 1,   // 0-1
    PAIRITY_EVEN = 3,   // 1-1
    
    BAURD_RATE_9600   = 3,  // 0-1-1 
    BAURD_RATE_115200 = 7,  // 1-1-1 
    
    AIR_DATA_RATE_LONG_RANGE   = 0, // 0-0-0 | 0.3k
    AIR_DATA_RATE_MEDIUM_RANGE = 2, // 0-1-0 | 2.4k Default
    AIR_DATA_RATE_SMALL_RANGE  = 5, // 1-0-1 | 19.2K

    WIRLESS_WAKE_UP_FAST   = 0, // 0-0-0
    WIRLESS_WAKE_UP_MEDIUM = 4, // 1-0-0 
    WIRLESS_WAKE_UP_SLOW   = 7, // 1-1-1

    TRANSMISSION_POWER_HIGH    = 0, // 0-0
    TRANSMISSION_POWER_27dBm   = 1, // 0-1
    TRANSMISSION_POWER_24dBm   = 2, // 1-0
    TRANSMISSION_POWER_LOW     = 3, // 1-1


}LoRa_Commands ;

typedef struct{

    LoRa_Commands paramState;   //HEAD 8bit 
    
    uint8_t HIGH_ADRESS_CODE;   //ADDH 8bit 
    uint8_t LOW_ADRESS_CODE;    //ADDL 8bit 

    //bool brodcastModeEnable;  //IF it is true : xFFFF HIGH_ADRESS_CODE & LOW_ADRESS_CODE

    LoRa_Commands pairityState; //SPED bit 7-6
    LoRa_Commands baudRate;     //SPED bit 5-4-3
    LoRa_Commands airDataRate;  //SPED bit 2-1-0

    //00H-1FH, correspond to 410~441MHz DEFAULT 17H 433MHz
    uint16_t channelFrequency;       //CHANNEL bit 0-1-2-3-4 in use; 5-6-7 reserved 

    bool fixedTransmissionEnable;    //OPTION   bit 7
    bool ioDriveModeEnable;                //OPTION   bit 6 
    LoRa_Commands wirlessWakeUpTime; //OPTION   bit 5-4-3 
    bool enableFEC;                  //OPTION   bit 2 
    LoRa_Commands transmissionPower; //OPTION   bit 1-0


}LoRa_Command_Setup;

typedef struct{

    uint8_t M0;
    uint8_t M1;
    uint32_t GPIO_PORT;    //PORT FOR M0 & M1
    uint32_t USART_PIN;    //COMMUNUCATION USART_PIN 
    
}LoRa_Configs;

void LoRa_INIT();
void LoRa_SendCommand(LoRa_Command_Setup*);
void LoRa_ReciveResponse(LoRa_Configs*,uint8_t*);
void LoRa_ModeSet(LoRa_Mode*,LoRa_Configs*);
bool LoRa_ReadOperatingParams(LoRa_Mode* ,LoRa_Command_Setup*,LoRa_Configs*,uint8_t*);
bool LoRa_ReadVersionNumber(LoRa_Mode*, LoRa_Command_Setup*,LoRa_Configs*,uint8_t*);
bool LoRa_Reset(LoRa_Mode*,LoRa_Command_Setup*,LoRa_Configs*,uint8_t*);

#endif // !LORA_CONFIG
