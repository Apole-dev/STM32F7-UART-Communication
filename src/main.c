/* src/main.c */

#include <stm32f722xx.h>
#include "usart.h"
/*
 * USER-BUTTON PC13
 * BLUE-LED PB7
 */



void SystemInit(void); 

void delay(volatile uint32_t count) {
  while (count--)
    ;

}

void LED_INIT(void);
void GPIO_Init(void);
void EXTI_Init(void);

 

int main(void) {
 
  void SystemInit(void);
  

  SET_USART_GPIO();
  USART_INIT();

  
  while (1) {
     //SEND_USART_DATA('A');
    char recived = RECIVE_USART_DATA();
    delay(1000000);
    ASSIGN_LED_USART(recived);

     delay(1000000);
  // Add a delay to slow down the transmission
  }
}

void NMI_Handler(void) {
  while (1)
    ;
}

void HardFault_Handler(void) {
  while (1)
    ;
}
