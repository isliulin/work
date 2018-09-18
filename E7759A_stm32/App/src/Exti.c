/*
********************************************************************************
*  Copyright (C), 2009-2013, ����˼׳�����з�����
*
*  ��Ŀ���ƣ�xxxx
*  
*  �ļ�����: xxxx.c
*
*  �ļ�������xxxx
*             
*             
*  �� �� ��: �ʺ���
*
*  �������ڣ�2013-03-18 
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
#include "Exti.h"
#include "shell.h"
#include "Delay.h"
#include "main.h"

volatile u8 acconoff=ACC_ON;

/*
********************************************************************************
*  ��������: EXTI_Configuration
*
*  ��������: �жϳ�ʼ��
*
*  �������: ��
*
*  �������: ��
*
*  �� �� ֵ: ��
*
********************************************************************************
*/
void EXTI0_Configuration(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;  
    NVIC_InitTypeDef NVIC_InitStructure;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);  
    EXTI_ClearITPendingBit(EXTI_Line0);
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;  
    EXTI_Init(&EXTI_InitStructure); 

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0A;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;     
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
    NVIC_Init(&NVIC_InitStructure);
}

void EXTI0_IRQHandler(void)
{
    u8 rdata;
	  u8 i;
	  static u8 accon_cnt = 0;
    static u8 accoff_cnt = 0;
    RTU_DEBUG("EXTI0_IRQHandler\r\n");//OK
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
				EXTI_ClearITPendingBit(EXTI_Line0); /* ����жϱ�־λ */
				//do something
				DelayUS(5);
				for(i=0;i<3;i++)
				{
          rdata=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
					if(0 == rdata){
						accoff_cnt = 0;
						accon_cnt++;
						if(accon_cnt == 2)
						{
		            GPIO_SetBits(GPIOA, GPIO_Pin_11);
							  accon_cnt = 0;
								acconoff=ACC_ON;
						}
					}
					else{
							accon_cnt = 0;
							accoff_cnt++;
						if(accoff_cnt == 2)
						{
							GPIO_ResetBits(GPIOA, GPIO_Pin_11); 
							accoff_cnt = 0;
							acconoff = ACC_OFF;
						}
					}				
			 }
    }
}






