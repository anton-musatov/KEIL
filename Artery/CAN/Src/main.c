#include "at32f413.h"                   // Device header

#include "ClockInit.h"
#include "GPIO.h"
#include "CAN.h"

void MCO_Init(int sourse);

int main() 
{
	InitClk();
	system_core_clock_update();
	SysTick_Config(200000000/1000);
	InitMCO(7);
	InitGPIO();
	InitCAN();
	
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
		TOGGLE_BIT(GPIOC->odt, 13);
		cnt = 0;
	}
}

