#include "at32f413.h"                   // Device header
#include "ClockInit.h"

void ClkInit(void)
{
	
	//CRM->ctrl_bit.hicken = 0;
	uint16_t i;
	
	while ((CRM->ctrl_bit.hickstbl) && (i < 1000))
	{
		i++;		
	}
	
	CRM->ctrl_bit.hexten = 1;
	
	while (!(CRM->ctrl_bit.hextstbl));
		
	CRM->ctrl_bit.cfden = 1;

	CRM->ctrl_bit.pllen = 0;
	while (CRM->ctrl_bit.pllstbl){};
		
	CRM->cfg_bit.pllrange = 1;
	CRM->cfg_bit.pllmult_l = 8;
	CRM->cfg_bit.pllmult_h = 1;
	CRM->cfg |= CRM_AHB_DIV_1;
	CRM->cfg |= CRM_APB1_DIV_2;
	CRM->cfg |= CRM_APB2_DIV_2;
	CRM->cfg_bit.pllhextdiv = 0;
	CRM->cfg_bit.pllrcs = 1;
	 
	CRM->ctrl_bit.pllen = 1;		
	while (!(CRM->ctrl_bit.pllstbl)){};
		
	CRM->misc3_bit.auto_step_en = 3;
     
	CRM->cfg_bit.sclksel = CRM_SCLK_PLL;	 
	while(!(CRM->cfg_bit.sclksts == CRM_SCLK_PLL)){};
		 
	CRM->ctrl_bit.hicken = 0;
}

void MCOInit(int sourse)
{
  CRM->apb2en_bit.gpioaen = 1; //Включаем тактирование порта PA
  
  //Настраиваем порт в режим альтернативной функции
	GPIOA->cfghr_bit.iofc8 = 2; 		//Сбрасываем биты в ноль
	GPIOA->cfghr_bit.iomc8 = 3; 	  
  
	CRM->cfg_bit.clkout_sel = sourse;
}
