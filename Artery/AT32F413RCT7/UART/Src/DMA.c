#include "DMA.h"

#define BUF_SIZE  8 

uint8_t txData[BUF_SIZE];
uint8_t rxData[BUF_SIZE];

void InitDMA(void)
{
	//RCM->AHB1CLKEN_B.DMA2EN			 = BIT_SET;
	CRM->ahben_bit.dma1en = 1;
	
	//DMA1->src_sel1_bit.ch5_src = 25;
	DMA1_CHANNEL5->ctrl_bit.chpl = 0;
	DMA1_CHANNEL5->ctrl_bit.pincm = 0;
	DMA1_CHANNEL5->ctrl_bit.mincm = 1;
	DMA1_CHANNEL5->ctrl_bit.dtd = 0;
	DMA1_CHANNEL5->paddr = (uint32_t)&(USART1->dt);
	DMA1_CHANNEL5->maddr = (uint32_t)&rxData;
	DMA1_CHANNEL5->dtcnt = BUF_SIZE;
	DMA1_CHANNEL5->ctrl_bit.hdtien = 1;
	DMA1_CHANNEL5->ctrl_bit.fdtien = 1;
	DMA1_CHANNEL5->ctrl_bit.chen = 1;
	
	//DMA2_Stream2->SCFG_B.CHSEL	 = DMA_SCFG_CHSEL4;
	//DMA2_Stream2->SCFG_B.PRILCFG = BIT_RESET;
	//DMA2_Stream2->SCFG_B.PERIM   = BIT_RESET;
	//DMA2_Stream2->SCFG_B.MEMIM   = BIT_SET;
	//DMA2_Stream2->SCFG_B.DIRCFG  = BIT_RESET;
	//DMA2_Stream2->PADDR 				 = (uint32_t)&(USART1->DATA);
	//DMA2_Stream2->M0ADDR				 = (uint32_t)rxData;
	//DMA2_Stream2->NDATA					 = BUF_SIZE;
	//DMA2_Stream2->SCFG_B.HTXIEN  = BIT_SET;
	//DMA2_Stream2->SCFG_B.TXCIEN  = BIT_SET;
	//DMA2_Stream2->SCFG_B.EN			 = BIT_SET;
	
	//DMA1->src_sel1_bit.ch7_src = 26;
	DMA1_CHANNEL4->ctrl_bit.chpl = 0;
	DMA1_CHANNEL4->ctrl_bit.pincm = 0;
	DMA1_CHANNEL4->ctrl_bit.mincm = 1;
	DMA1_CHANNEL4->ctrl_bit.dtd = 1;
	DMA1_CHANNEL4->paddr = (uint32_t)&(USART1->dt);
	DMA1_CHANNEL4->maddr = (uint32_t)&rxData;
	DMA1_CHANNEL4->dtcnt = BUF_SIZE/2;
	DMA1_CHANNEL4->ctrl_bit.fdtien = 1;
	
	//DMA2_Stream7->SCFG_B.CHSEL	 = DMA_SCFG_CHSEL4;
	//DMA2_Stream7->SCFG_B.PRILCFG = BIT_SET;
	//DMA2_Stream7->SCFG_B.PERIM	 = BIT_RESET;
	//DMA2_Stream7->SCFG_B.MEMIM	 = BIT_SET;
	//DMA2_Stream7->SCFG_B.DIRCFG	 = BIT_SET;
	//DMA2_Stream7->PADDR					 = (uint32_t)&(USART1->DATA);
	//DMA2_Stream7->M0ADDR				 = (uint32_t)rxData;
	//DMA2_Stream7->NDATA					 = BUF_SIZE/2;
	//DMA2_Stream7->SCFG_B.TXCIEN	 = BIT_SET;
	
	NVIC_EnableIRQ(DMA1_Channel5_IRQn);
	NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void DMA1_Channel5_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(DMA1_Channel5_IRQn);
	if (DMA1->sts_bit.hdtf5)
	{
		DMA1->clr_bit.hdtfc5 = 1;
		DMA1_CHANNEL4->maddr = (uint32_t)rxData;
		DMA1_CHANNEL4->ctrl_bit.chen = 1;
	}
	else
	{
		DMA1_CHANNEL5->ctrl_bit.chen = 0;
		DMA1->clr_bit.fdtfc5 = 1;
		DMA1_CHANNEL4->maddr = (uint32_t)&rxData[BUF_SIZE/2];
		DMA1_CHANNEL4->ctrl_bit.chen = 1;
		DMA1_CHANNEL5->dtcnt = BUF_SIZE;
		DMA1_CHANNEL5->ctrl_bit.chen = 1;
	}
}

void DMA1_Channel4_IRQHandler(void)
{
	DMA1_CHANNEL4->ctrl_bit.chen = 0;
	DMA1_CHANNEL4->dtcnt = BUF_SIZE/2;
	NVIC_ClearPendingIRQ(DMA1_Channel4_IRQn);
	DMA1->clr_bit.fdtfc4 = 1;
	DMA1->clr_bit.hdtfc4 = 1;
}
