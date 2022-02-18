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
	delay_init(72);	          //延时初始化
	NVIC_Configuration();
	uart_init(9600);         //串口初始化
 	LED_Init();		            //LED端口初始化
	BEEP_Init();              //蜂鸣器初始化
	KEY_Init();               //按键端口初始化
	Timerx_Init(5000,7199);   //10Khz的计数频率，计数到5000为500ms 
	UltrasonicWave_Configuration();               //对超声波模块初始化

	TIM3_PWM_Init(899,0);	
	TIM4_PWM_Init(899,0);
	
	while(1)
	{
		UltrasonicWave_StartMeasure();                //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
	}
 }


 