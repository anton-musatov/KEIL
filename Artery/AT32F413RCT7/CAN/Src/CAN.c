#include "CAN.h"

void InitCAN(void)
{
	/*-------------------------------------------------*/
	/*--------------------PINS-------------------------*/
	/*-------------------------------------------------*/
	CRM->apb2en_bit.gpioaen = 1; //Включаем тактирование порта PA
  
  //Настраиваем порт в режим альтернативной функции
	GPIOA->cfghr_bit.iomc11 = 3; 
	GPIOA->cfghr_bit.iofc11 = 2; 		
	
	GPIOA->cfghr_bit.iomc12 = 3;
	GPIOA->cfghr_bit.iofc12 = 2; 		
	/*-------------------------------------------------*/
	
	/*-------------------------------------------------*/
	/*--------------------CAN--------------------------*/
	/*-------------------------------------------------*/
	CRM->apb1en_bit.can1en = 1;
	
	CAN1->mctrl_bit.fzen = 1;
	CAN1->mctrl_bit.prsfen = 1;
	
	CAN1->mctrl_bit.dzen = 0;
	
	CAN1->btmg = 0x001c0018;
	
	CAN1->mctrl_bit.fzen = 0;
	
	CAN1->inten_bit.rf0mien = 1;
	//CAN1->inten_bit.rf1mien = 1;
	//CAN1->inten_bit.tcien = 1;
	
	CAN1->fctrl_bit.fcs = 1;
	CAN1->fmcfg_bit.fmsel0 = 0;
	CAN1->fbwcfg_bit.fbwsel0 = 1;
	CAN1->frf_bit.frfsel0 = 0;
	CAN1->ffb[0].ffdb1 = 0x4;
	CAN1->ffb[0].ffdb2 = 0x4;
	CAN1->fctrl_bit.fcs = 0;
	CAN1->facfg_bit.faen0 = 1;
	
	NVIC_EnableIRQ(USBFS_L_CAN1_RX0_IRQn);
	/*-------------------------------------------------*/
}

void CAN_Transmit(uint32_t id, uint8_t* data)
{
  uint32_t tx_msg_data[2] = {0, 0};
  for (uint8_t i = 0; i < 8; i++)
  {
      tx_msg_data[i / 4] |= (uint32_t)data[i] << (i - (i / 4) * 4) * 8;
  }
	
	CAN1->tx_mailbox[0].tmi_bit.tmidsel = 1;
	CAN1->tx_mailbox[0].tmi |= (id << 3);
	CAN1->tx_mailbox[0].tmdtl = tx_msg_data[0];
	CAN1->tx_mailbox[0].tmdth = tx_msg_data[1];
	CAN1->tx_mailbox[0].tmi_bit.tmsr = 1;

}

void USBFS_L_CAN1_RX0_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(USBFS_L_CAN1_RX0_IRQn);
	uint32_t id = CAN1->fifo_mailbox[0].rfi_bit.rfeid;
	static uint8_t data[8];
	
	data[0] = (uint8_t)((CAN1->fifo_mailbox[0].rfdtl & 0x000000FF) >> 0 );
  data[1] = (uint8_t)((CAN1->fifo_mailbox[0].rfdtl & 0x0000FF00) >> 8 );
  data[2] = (uint8_t)((CAN1->fifo_mailbox[0].rfdtl & 0x00FF0000) >> 16);
  data[3] = (uint8_t)((CAN1->fifo_mailbox[0].rfdtl & 0xFF000000) >> 24);
  data[4] = (uint8_t)((CAN1->fifo_mailbox[0].rfdth & 0x000000FF) >> 0 );
  data[5] = (uint8_t)((CAN1->fifo_mailbox[0].rfdth & 0x0000FF00) >> 8 );
  data[6] = (uint8_t)((CAN1->fifo_mailbox[0].rfdth & 0x00FF0000) >> 16);
  data[7] = (uint8_t)((CAN1->fifo_mailbox[0].rfdth & 0xFF000000) >> 24);
	
	CAN_Transmit(id, (uint8_t*)&data);
	CAN1->rf0_bit.rf0r = 1;

}
