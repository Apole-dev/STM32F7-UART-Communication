#include "stm32f722xx.h"
#include <stdint.h>
#include <usart.h>

/*
 * TTL
 * ------
 * RX WHITE (B6)
 * TX BROWN (B7)
 *
 * stm32f722xx
 * -----
 * B6 TX 
 * B7 RX 
 */



void SET_USART_GPIO(){
  RCC->AHB1ENR |= (1<<1); //Enable GPIOB CLOCK

  GPIOB->MODER |= (1<<0); //GPIOB0 Moder output mode green led

  GPIOB->MODER |= (2<<(2*6)); //ENABLE ALTERNATE MODE FOR B6 PIN
  GPIOB->MODER |= (2<<(2*7));
  GPIOB->PUPDR &= ~(3 << (7 * 2));  // Pull-up/pull-down'ı sıfırla
  GPIOB->PUPDR |= (2 << (7 * 2));   // Pull-down'ı etkinleştir

  GPIOB->OSPEEDR |= (2<<(2*6)); //SET P6 SPEED HIGH 01
  GPIOB->OSPEEDR |= (2<<(2*7)); //SET P6 SPEED HIGH 01

  GPIOB->AFR[0] |= (7<<(4*6)); // ENABLE AFR7 0111 USART1_TX PIN B6
  GPIOB->AFR[0] |= (7<<(4*7)); // ENABLE AFR7 0111 USART1_RX PIN B/

}


void USART_INIT(void){

  //SET RCC-APB2
  RCC->APB2ENR |= (1<<4);//USART1- ENABLE

  USART1->CR1 &= ~(1<<0); // MAKE SURE USART DISABLED
  
  //SET M0-M1 FOR 8BIT WORD LENGTH
  USART1->CR1 &= ~(1<<12); // M0 = 0
  USART1->CR1 &= ~(1<<28); // M1 = 0 
  //STOP BIT 0-0 MEAN 1
  USART1->CR2 &= ~(1<<13);
  USART1->CR2 &= ~(1<<12);
  
  //UART OVER SAMPLING MODE 16
  USART1->CR1 &= ~(1<<15); 


  //CLOCK 16MHZ 

  USART1->BRR =139;

  USART1->CR1 |= (1<<3); //TRANSMIT ENABLE
  USART1->CR1 |= (1<<2); //RECIVER ENABLE

  USART1->CR1 |= (1<<0); //USART1-ENABLE


}


//SEND DATA
void SEND_USART_DATA(uint8_t data){

  //Wait until ISR TXE has data in it
  while ((USART1->ISR & (1<<7)) == 0) {
  
  }
  USART1->TDR = data;
}


//RECIE DATA
uint8_t RECIVE_USART_DATA(){
  uint8_t data = 0;

  while ((USART1->ISR & (1<<5)) == 0) {
  
  }
  data = USART1->RDR;
  return data;
}

void ASSIGN_LED_USART(uint8_t state){
  
  switch (state) {
    case '1':
      GPIOB->ODR |= (1<< 0); //green led Enable
    break;
    case '2':
      GPIOB->ODR &= ~(1<<0);//green led disable
    break;
      default:
    break;
  }
  
}
