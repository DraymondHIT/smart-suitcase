#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "beep.h"
#include "usart.h"
#include "exti.h"
#include "timer.h"
#include "UltrasonicWave.h"
#include "stm32f10x.h"

 int main(void)
 {
 // SystemInit();
	u16 adcx;
	float temp;
	delay_init(72);	          //��ʱ��ʼ��
	NVIC_Configuration();
	uart_init(9600);         //���ڳ�ʼ��
 	LED_Init();		            //LED�˿ڳ�ʼ��
	BEEP_Init();              //��������ʼ��
	KEY_Init();               //�����˿ڳ�ʼ��
	Timerx_Init(5000,7199);   //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	UltrasonicWave_Configuration();               //�Գ�����ģ���ʼ��

	TIM3_PWM_Init(899,0);	
	TIM4_PWM_Init(899,0);
	
	while(1)
	{
		UltrasonicWave_StartMeasure();                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
	}
 }


 