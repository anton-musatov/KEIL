#include "at32f413.h"                   // Device header

#include "ClockInit.h"
#include "GPIO.h"

void MCO_Init(int sourse);

int main() 
{
	ClkInit();
	system_core_clock_update();
	SysTick_Config(200000000/1000);
	MCOInit(7);
	GPIOInit();
	
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
	}
}

