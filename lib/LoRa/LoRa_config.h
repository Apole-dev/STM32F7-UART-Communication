/*
 * Documentation :  https://www.rcscomponents.kiev.ua/datasheets/e32-433t30d_usermanual_en_v1_6.pdf
*/


#ifndef LORA_CONFIG
#define LORA_CONFIG


#include <stdint.h>


const uint8_t LORA_READ_PARAM[3] = {0xC1,0xC1,0xC1} ;
const uint8_t LORA_READ_VERSION[3] = {0xC3,0xC3,0xC3};
const uint8_t LORA_RESET[3] = {0xC4,0xC4,0xC4};

typedef enum {
    // BYTE-0
    SAVE_PARAM = 0xC0,
    
    //BYTE-1
    DO_NOT_SAVE_PARAM =0xC2,


    //BRODCAST MODE SECTION
    //BRODCAST_MODE_ENABLE = 0xFFFF,

    /*
     * BYTE-3
     * SPED SECTION : 8 BIT 
     * 2 + 3 + 3 = 8 BIT = 1 BYTE
     */

    //PAIRITY 2bit
    PAIRITY_ENABLE = 2, //1-0 
    PAIRITY_DISABLE = 0, //0-0 or 1-1 
    
    //BAURD RATE 3bit
    BAURD_RATE_9600 = 3, // 0-1-1 
    BAURD_RATE_115200 = 7, // 1-1-1 
    
    //AIR DATA RATE 3bit
    AIR_DATA_RATE = 2, // 0-1-0 

    /*
     * BYTE-4
     *  CHANNEL SECTION
     *  00H-1FH, correspond to 410~441MHz 
     */

    /*
     * BYTE-5
     *  OPTION SECTION
     *
     *
     */



}LoRa_Commands ;

typedef struct{

    LoRa_Commands paramState;
    LoRa_Commands pairityState;
    LoRa_Commands baudRate;
    LoRa_Commands airDataRate;
    
    int8_t BRODCAST_MODE_ENABLE; //Can be set as an bool 


}LoRa_Command_Setup;

void LoRa_INIT();
void LoRa_SendCommand();
void LoRa_ReciveResponse();
void LoRa_GetConfig();
void LoRa_SetConfig();

#endif // !LORA_CONFIG
