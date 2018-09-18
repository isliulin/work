/*
********************************************************************************
*  Copyright (C), 2009-2012, ����˼׳�����з�����
*
*  ��Ŀ���ƣ�E7759A
*  
*  �ļ�����: Main.c
*
*  �ļ�������E7759A������main
*             
*             
*  �� �� ��: zhexuan.wei
*
*  �������ڣ�2017-06-18 
*
*  �� �� �ţ�V1.0
*
*  �޸ļ�¼�� 
*             
*      1. ��    �ڣ� 
*         �� �� �ˣ� 
*         �����޸ģ� 
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
*  ��������: TIMER_Configuration
*
*  ��������: ��ʱ����ʼ��
*
*  �������: ��
*
*  �������: ��
*
*  �� �� ֵ: ��
*
********************************************************************************
*/
void TIMER_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE); /* ʱ��ʹ��*/
    TIM_DeInit(TIM2); /*���½�Timer����Ϊȱʡֵ*/
    TIM_TimeBaseStructure.TIM_Period=20000-1; /*�Զ���װ�ؼĴ������ڵ�ֵ(����  ֵ) 1s*/
    TIM_TimeBaseStructure.TIM_Prescaler= (uint16_t) (SystemCoreClock / 20000) - 1;  /* ʱ��Ԥ��Ƶ�� 72M/20000 -1 */  
 
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;  /* ������Ƶ */  
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; /* ���ϼ���ģʽ */  
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);  
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);  /* �������жϱ�־ */    
	
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
*  ��������: main
*
*  ��������: ��������Ӧ�ó������
*
*  �������: ��
*
*  �������: ��
*
*  �� �� ֵ: ��
*
********************************************************************************
*/

u8 data[4] = {0x01,0x02,0x03,0x04};

int main(void)
{	
	  u8 temp;
    u8 i=0;
	
    BSP_Init();
	  //shell��ʼ��
    ShellInit();
    Com3Init(&COM3, 115200, COM_PARA_8N1);	
    //ϵͳ��ʱ����ʼ��
    systick_init();
	  TIMER_Configuration(); 	
	
	  //RTU_DEBUG("main\r\n");
    //���������ʱ��ƽ����ղ���'C'�ַ���
	  DelayMS(500);
    ComxPutChar(&COM3,CRC16);
	  ComxPutChar(&COM1,CRC16);
    TIM_Cmd(TIM2, ENABLE);	
		Main_Menu();
	
}
