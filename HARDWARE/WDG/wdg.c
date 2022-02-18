#include "wdg.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 

//Mini STM32������
//���Ź� ��������		   


//All rights reserved
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(prer);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	
	IWDG_SetReload(rlr);  //����IWDG��װ��ֵ
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
}
//ι�������Ź�
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();										   
}


//����WWDG������������ֵ,Ĭ��Ϊ���.
u8 WWDG_CNT=0x7f;

void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //   WWDGʱ��ʹ��

	WWDG_SetPrescaler(fprer);////����IWDGԤ��Ƶֵ

	WWDG_SetWindowValue(wr);//���ô���ֵ

	WWDG_Enable(tr);	 //ʹ�ܿ��Ź� ,	���� counter .                  

	WWDG_ClearFlag();

	WWDG_NVIC_Init();//��ʼ�����ڿ��Ź� NVIC

	WWDG_EnableIT(); //�������ڿ��Ź��ж�
} 
//������WWDG��������ֵ
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);	 
}
//���ڿ��Ź��жϷ������
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ2�������ȼ�3����2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //��ռ2�������ȼ�3����2	
	NVIC_Init(&NVIC_InitStructure);//NVIC��ʼ��
}

void WWDG_IRQHandler(void)
	{
	// Update WWDG counter
	WWDG_SetCounter(0x7F);	  //�������˾��,���ڿ��Ź���������λ
	// Clear EWI flag */
	WWDG_ClearFlag();	  //�����ǰ�����жϱ�־λ
	// Toggle GPIO_Led pin 7 */
	LED1=!LED1;
	}

