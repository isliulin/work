/*
**********************************************************************************************************
*  Copyright (C), 2009-2013, ����˼׳�����з�����
*
*  ��Ŀ���ƣ� xxxx
*  
*  �ļ�����:  xxxx.h
*
*  �ļ������� xxxx
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
**********************************************************************************************************
*/
#ifndef __FLASH_H
#define __FLASH_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32f10x.h"

#define PAGE_ADDR  0x803F800
	
/*
*********************************************************************
*  ȫ�ֺ궨��
*********************************************************************
*/
 



/*
*********************************************************************
*  �ࡢ�ṹ�����Ͷ���
*********************************************************************
*/


/*
*********************************************************************
*  �ⲿ���ñ�������
*********************************************************************
*/

/*
*********************************************************************
*  �ⲿ���ú�������
*********************************************************************
*/
u8 MemWriteData(u32 addr,u16 *data,u16 num);
u8 MemReadData(u32 addr,u16 *data,u16 num);  



#ifdef __cplusplus
}
#endif

#endif /* __FLASH_H */
