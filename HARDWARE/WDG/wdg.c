#include "wdg.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 

//Mini STM32开发板
//看门狗 驱动代码		   


//All rights reserved
void IWDG_Init(u8 prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(rlr);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();										   
}


//保存WWDG计数器的设置值,默认为最大.
u8 WWDG_CNT=0x7f;

void WWDG_Init(u8 tr,u8 wr,u32 fprer)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //   WWDG时钟使能

	WWDG_SetPrescaler(fprer);////设置IWDG预分频值

	WWDG_SetWindowValue(wr);//设置窗口值

	WWDG_Enable(tr);	 //使能看门狗 ,	设置 counter .                  

	WWDG_ClearFlag();

	WWDG_NVIC_Init();//初始化窗口看门狗 NVIC

	WWDG_EnableIT(); //开启窗口看门狗中断
} 
//重设置WWDG计数器的值
void WWDG_Set_Counter(u8 cnt)
{
    WWDG_Enable(cnt);	 
}
//窗口看门狗中断服务程序
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占2，子优先级3，组2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //抢占2，子优先级3，组2	
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化
}

void WWDG_IRQHandler(void)
	{
	// Update WWDG counter
	WWDG_SetCounter(0x7F);	  //当禁掉此句后,窗口看门狗将产生复位
	// Clear EWI flag */
	WWDG_ClearFlag();	  //清除提前唤醒中断标志位
	// Toggle GPIO_Led pin 7 */
	LED1=!LED1;
	}

