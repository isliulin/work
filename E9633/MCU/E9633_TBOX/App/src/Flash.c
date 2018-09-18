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
#include "Flash.h"
#include "shell.h"
#include "Delay.h"


u8 MemWriteData(u32 addr,u16 *data,u16 num)
{
    FLASH_Status temp_stat;
    u32 temp_addr = addr;
    u16 i;
     
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); 
    //temp_stat=FLASH_ErasePage(temp_addr); 
		
    for(i=0;i<num;i++)
    { 
			
        temp_stat = FLASH_ProgramHalfWord((temp_addr +i*2),data[i]);  //flash  Ϊһ���ֽڴ洢��16λ���ݱ����ַ��2 
        if(temp_stat != FLASH_COMPLETE)
         {
              FLASH_Lock();
              //return 0;
         }
         
	  }
	  FLASH_Lock();
    return 1;
}

u8 MemReadData(u32 addr,u16 *data,u16 num)                                
 {
      u32 *temp_addr = (u32 *)addr;
      u16 i;
 
      for(i=0;i<num;i++)
      {
         data[i] = *(temp_addr +i*2);
      }    			
      return 1;                                                                                                        
 }
 
 u8 MemReadByte(u32 addr,u8 *data,u16 num)                                
 {
      u32 *temp_addr = (u32 *)addr;
      u16 i;
 
      for(i=0;i<num;i++)
      {
         data[i] = *(temp_addr +i*2);
      }    			
      return 1;                                                                                                        
 }

void MemReadSN(u32 addr,u8 *data,u16 num)
{
	  u8 i;
		for(i=0;i<num;i++)
	  {
			  MemReadByte(PAGE_ADDR+16+(i*2),&data[i],1);
		}
}
void FlashClean(u32 addr)
{
	  FLASH_Status temp_stat;
	  u32 temp_addr = addr;
	
		FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); 
    temp_stat=FLASH_ErasePage(temp_addr); 
    if(temp_stat != FLASH_COMPLETE)
    {
         FLASH_Lock();
        
    }
		FLASH_Lock();
}

void MemWriteSN(u32 addr,u16 *data,u16 num)
{
	  u8 i;
		FLASH_Status temp_stat;
    u32 temp_addr = addr;
 
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR); 

    for(i=0;i<num;i++)
    { 
			
        temp_stat = FLASH_ProgramHalfWord((temp_addr +i*2),data[i]);  //flash  Ϊһ���ֽڴ洢��16λ���ݱ����ַ��2 
        if(temp_stat != FLASH_COMPLETE)
         {
              FLASH_Lock();
            
         }
         
	  }
	  FLASH_Lock();
}

