#include "UART.h"

void InitUART(void)
{
	/*------------------------------------------------*/
	/*----------------------PINS----------------------*/
	/*------------------------------------------------*/
	CRM->apb2en_bit.gpioaen = 1;
	
	GPIOA->cfghr_bit.iofc9 = 2; 		
	GPIOA->cfghr_bit.iomc9 = 3;
	GPIOA->cfghr_bit.iofc10 = 2; 		
	GPIOA->cfghr_bit.iomc10 = 3;
	
	/*------------------------------------------------*/
	
	/*------------------------------------------------*/
	/*----------------------UART----------------------*/
	/*------------------------------------------------*/
	CRM->apb2en_bit.usart1en = 1;
	
	
	USART1->baudr_bit.div = 1736;
	USART1->ctrl1_bit.uen = 1;
	USART1->ctrl1_bit.ten = 1;
	USART1->ctrl1_bit.ren = 1;
	//USART1->ctrl3_bit.dmaten = 1;
	//USART1->ctrl3_bit.dmaren = 1;

	//USART1->CTRL1_B.OSMCFG    = BIT_SET;
	//USART1->CTRL3_B.DMARXEN  	= BIT_SET;
	//USART1->CTRL3_B.DMATXEN  	= BIT_SET;
	/*------------------------------------------------*/
}

void UART_tx(uint8_t * TXdata, uint8_t size)
{	
	uint8_t count = 0;
	while (count < size)
	{
		while (!(USART1->sts_bit.tdc));
		USART1->dt = TXdata[count];
		count++;
	}
}
