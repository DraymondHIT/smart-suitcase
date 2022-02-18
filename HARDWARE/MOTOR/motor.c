#include "motor.h"

void motor1_go(u16 pwm)
{
	TIM_SetCompare2(TIM3,pwm);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
}

void motor1_back(u16 pwm)
{
	TIM_SetCompare2(TIM3,pwm);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}

void motor1_stop(void)
{
	TIM_SetCompare2(TIM3,0);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
}

void motor2_go(u16 pwm)
{
	TIM_SetCompare2(TIM4,pwm);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
}

void motor2_back(u16 pwm)
{
	TIM_SetCompare2(TIM4,pwm);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);	
	GPIO_SetBits(GPIOB,GPIO_Pin_6);
}

void motor2_stop(void)
{
	TIM_SetCompare2(TIM4,0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}

void left(void)
{
	motor1_go(300);
	motor2_go(400);
	delay_ms(300);
}

void right(void)
{
	motor2_go(300);
	motor1_go(400);
	delay_ms(300);
}

void go(void)
{
	motor1_go(300);
	motor2_go(300);
	delay_ms(300);
}

void stop(void)
{
	motor1_stop();
	motor2_stop();
	delay_ms(100);
}


