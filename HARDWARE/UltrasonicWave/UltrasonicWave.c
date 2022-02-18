#include "UltrasonicWave.h"
#include "usart.h"
#include "timer.h"
#include "beep.h"
#include "delay.h"
#include "math.h"
#include "motor.h"

#define	TRIG_PORT      GPIOC		//TRIG       
#define	ECHO_PORT      GPIOC		//ECHO 
#define	TRIG_PIN       GPIO_Pin_8   //TRIG       
#define	ECHO_PIN       GPIO_Pin_7	  //ECHO   
#define TRIG_PORT2     GPIOE    //TRIG
#define ECHO_PORT2     GPIOE    //ECHO
#define TRIG_PIN2      GPIO_Pin_5   //TRIG
#define ECHO_PIN2      GPIO_Pin_4   //ECHO

double UltrasonicWave_Distance,UltrasonicWave_Distance2,max=0,min=10000,sum=0;
int total=0,make=0,flag=0;

void UltrasonicWave_Configuration(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;	
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE);
    
		GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC8��TRIG
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
		GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 

		GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC7��ECH0
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
		GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //��ʼ��GPIOA

	  GPIO_InitStructure.GPIO_Pin = TRIG_PIN2;					 //PE5��TRIG
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
		GPIO_Init(TRIG_PORT2, &GPIO_InitStructure);	                 //��ʼ������GPIO 
	
	  GPIO_InitStructure.GPIO_Pin = ECHO_PIN2;					 //PE4��ECHO
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		     //��Ϊ����	         
		GPIO_Init(ECHO_PORT2, &GPIO_InitStructure);	                 //��ʼ������GPIO 

    //GPIOC.7 GPIOE.4	  �ж����Լ��жϳ�ʼ������
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);

		EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
			
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}


void EXTI9_5_IRQHandler(void)
{
		delay_us(10);		//��ʱ10us
		if(EXTI_GetITStatus(EXTI_Line7) != RESET)
		{
				TIM_SetCounter(TIM2,0);
				TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
		
				while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ

				TIM_Cmd(TIM2, DISABLE);			                                       //��ʱ��2ʧ��
				UltrasonicWave_Distance=TIM_GetCounter(TIM2)*340/200.0;									 //�������&&UltrasonicWave_Distance
		
				if(UltrasonicWave_Distance>0)
				{
						total++;
						if(UltrasonicWave_Distance<=300)
						{
								make++;
							  sum+=UltrasonicWave_Distance;
							  if(UltrasonicWave_Distance>max) max=UltrasonicWave_Distance;
							  else if(UltrasonicWave_Distance<min) min=UltrasonicWave_Distance;
						}
				}
			
				EXTI_ClearITPendingBit(EXTI_Line7);  //���EXTI7��·����λ
		}
}

void EXTI4_IRQHandler(void)
{
		delay_us(10);		                      //��ʱ10us
		if(EXTI_GetITStatus(EXTI_Line4) != RESET)
		{
				TIM_SetCounter(TIM2,0);
				TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
		
				while(GPIO_ReadInputDataBit(ECHO_PORT2,ECHO_PIN2));	                 //�ȴ��͵�ƽ

				TIM_Cmd(TIM2, DISABLE);			                                       //��ʱ��2ʧ��
				UltrasonicWave_Distance2=TIM_GetCounter(TIM2)*340/200.0;									 //�������&&UltrasonicWave_Distance
		
				if(UltrasonicWave_Distance2>0)
				{
						total++;
						if(UltrasonicWave_Distance2<=300)
						{
								make++;
							  sum+=UltrasonicWave_Distance2;
							  if(UltrasonicWave_Distance2>max) max=UltrasonicWave_Distance2;
							  else if(UltrasonicWave_Distance2<min) min=UltrasonicWave_Distance2;
						}
						
				}
				
				EXTI_ClearITPendingBit(EXTI_Line4);  //���EXTI4��·����λ
		}
}

//��ʼ����
void UltrasonicWave_StartMeasure(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;	
  	NVIC_Init(&NVIC_InitStructure);  

	  delay_us(50);
	  total=make=0;
	  max=0,min=10000,sum=0;
	  while(make<5&&total<=10)
		{
				GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ
				delay_us(20);		                      //��ʱ20US
				GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
		}
		delay_us(50);
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  	NVIC_Init(&NVIC_InitStructure);  
		
		if(make==5)
		{
				sum-=max+min;
			  UltrasonicWave_Distance=sum/3;
			  flag=1;
		}
		total=make=0;
		max=0,min=10000,sum=0;
		delay_us(400);

		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure); 
		
		delay_us(50);
		while(make<5&&total<=10)
		{
				GPIO_SetBits(TRIG_PORT2,TRIG_PIN2); 		  //��>10US�ĸߵ�ƽ
				delay_us(20);		                      //��ʱ20US
				GPIO_ResetBits(TRIG_PORT2,TRIG_PIN2);
		}
		delay_us(50);
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  	NVIC_Init(&NVIC_InitStructure); 

		if(make==5)
		{
				sum-=max+min;
			  UltrasonicWave_Distance2=sum/3;
				if(flag && UltrasonicWave_Distance+UltrasonicWave_Distance2>200)
				{
					  BEEP=1;
						delay_ms(500);
					  BEEP=0;
				}
				flag=0;
		}
		total=make=0;
		
		printf("distance:%.2lf cm",UltrasonicWave_Distance);
		UltrasonicWave_Distance2*=1.3;
		printf("distance2:%.2lf cm",UltrasonicWave_Distance2);
		
		if (UltrasonicWave_Distance<50||UltrasonicWave_Distance2<50)
		{
			stop();
		}
		else if (UltrasonicWave_Distance-UltrasonicWave_Distance2>5)
		{
			left();
		}
		else if (UltrasonicWave_Distance2-UltrasonicWave_Distance>5)
		{
			right();
		}
		else
		{
			go();
		}
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure); 
}



