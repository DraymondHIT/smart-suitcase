#ifndef __WDG_H
#define __WDG_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//���Ź� ��������		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/5/30
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  


void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);

void WWDG_Init(u8 tr,u8 wr,u32 fprer);//��ʼ��WWDG
void WWDG_Set_Counter(u8 cnt);       //����WWDG�ļ�����
void WWDG_NVIC_Init(void);
#endif
