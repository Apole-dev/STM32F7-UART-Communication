#ifndef USART_H

#define USART_H 

#include <stdint.h>
void SET_USART_GPIO(void);
void USART_INIT(void);
void SEND_USART_DATA(uint8_t);
uint8_t RECIVE_USART_DATA(void);
void ASSIGN_LED_USART(uint8_t);
#endif // !USART_H          
