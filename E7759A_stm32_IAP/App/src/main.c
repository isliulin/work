/*
********************************************************************************
*  Copyright (C), 2009-2012, 合众思壮深圳研发中心
*
*  项目名称：E7759A
*  
*  文件名称: Main.c
*
*  文件描述：E7759A主函数main
*             
*             
*  创 建 者: zhexuan.wei
*
*  创建日期：2017-06-18 
*
*  版 本 号：V1.0
*
*  修改记录： 
*             
*      1. 日    期： 
*         修 改 人： 
*         所作修改： 
*      2. ...
********************************************************************************
*/

#define MAIN_GLOBALS
#include "main.h"
#include "SysTick.h"
#include "Shell.h"
#include "bsp.h"
#include "bsp_iwdg.h"
#include <string.h>
#include "menu.h"
#include "flash_if.h"
#include "ymodem.h"

/*
********************************************************************************
*  函数名称: TIMER_Configuration
*
*  功能描述: 定时器初始化
*
*  输入参数: 无
*
*  输出参数: 无
*
*  返 回 值: 无
*
********************************************************************************
*/
void TIMER_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE); /* 时钟使能*/
    TIM_DeInit(TIM2); /*重新将Timer设置为缺省值*/
    TIM_TimeBaseStructure.TIM_Period=20000-1; /*自动重装载寄存器周期的值(计数  值) 1s*/
    TIM_TimeBaseStructure.TIM_Prescaler= (uint16_t) (SystemCoreClock / 20000) - 1;  /* 时钟预分频数 72M/20000 -1 */  
 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  /* 采样分频 */  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* 向上计数模式 */  
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);  /* 清除溢出中断标志 */    
	
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);  
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);  
}
/*
********************************************************************************
*  函数名称: main
*
*  功能描述: 主函数，应用程序入口
*
*  输入参数: 无
*
*  输出参数: 无
*
*  返 回 值: 无
*
********************************************************************************
*/

u8 data[4] = {0x01,0x02,0x03,0x04};

int main(void)
{	
	  u8 temp;
    u8 i=0;
	
    BSP_Init();
	  //shell初始化
    ShellInit();
    Com3Init(&COM3, 115200, COM_PARA_8N1);	
    //系统定时器初始化
    systick_init();
	  TIMER_Configuration(); 	
	
	  //RTU_DEBUG("main\r\n");
    //如果不加延时，平板会收不到'C'字符。
	  DelayMS(500);
    ComxPutChar(&COM3,CRC16);
	  ComxPutChar(&COM1,CRC16);
    TIM_Cmd(TIM2, ENABLE);	
		Main_Menu();
	
}

