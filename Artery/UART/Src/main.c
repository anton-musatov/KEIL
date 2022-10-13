#include "at32f413.h"                   // Device header

#include "ClockInit.h"
#include "GPIO.h"
#include "UART.h"
#include "DMA.h"

int main() 
{
	ClkInit();
	system_core_clock_update();
	SysTick_Config(system_core_clock/1000);
	MCOInit(7);
	GPIOInit();
	InitUART();
	//InitDMA();
	
	while (1)
	{
		
	}
}

void SysTick_Handler(void)
{
	static uint16_t cnt;
	if (cnt < 1000)
	{
		cnt++;
	}
	else
	{
		GPIOC->odt ^= 1<<13;
		cnt = 0;
		//uint8_t datatx[] = "Hello, World!\r\n";
		//UART_tx(&datatx[0], sizeof(datatx)-1);
	}
}

