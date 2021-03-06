/*
********************************************************************************
*  Copyright (C), 2009-2012, 合众思壮西安研发中心
*
*  项目名称：VS331
*  
*  文件名称: CanDrv.h
*
*  文件描述：CAN硬件驱动头文件
*             
*             
*  创 建 者: 皇海明
*
*  创建日期：2014-04-04 
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

#ifndef __CANDRV_H
#define __CANDRV_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef  CANDRV_GLOBALS
#define CANDRV_EXT
#else
#define CANDRV_EXT   extern
#endif

#include "stm32f10x.h"

/*
*********************************************************************
*  全局宏定义
*********************************************************************
*/
// CAN输入、输出队列长度定义
#define    LIST_CAN1_IN_NUM      128
#define    LIST_CAN2_IN_NUM      128

#define    LIST_CAN1_OUT_NUM     128
#define    LIST_CAN2_OUT_NUM     128

/*#define    CANQUE_TO_CANTXMSG(msg, que)  do{\
    (msg)->ExtId = (que)->Id;\
    (msg)->IDE = CAN_Id_Extended;\
    (msg)->RTR = CAN_RTR_Data;\
    (msg)->DLC = (que)->Dlc;\
    (msg)->Data[0] = (que)->Data[0];\
    (msg)->Data[1] = (que)->Data[1];\
    (msg)->Data[2] = (que)->Data[2];\
    (msg)->Data[3] = (que)->Data[3];\
    (msg)->Data[4] = (que)->Data[4];\
    (msg)->Data[5] = (que)->Data[5];\
    (msg)->Data[6] = (que)->Data[6];\
    (msg)->Data[7] = (que)->Data[7];\
}while(0)*/


/*
*********************************************************************
*  类、结构体类型定义
*********************************************************************
*/
typedef struct CANQUEDATA_STRUCT
{
    u32 Id;        // 数据扩展ID
    u8  Data[8];   // 数据域
    u8  Dlc;       // 数据长度
}CANQUEDATA;

// 串口数据队列结构体
typedef struct canqueuelist_t
{
    u16       head;              /* 队列前指针 */
    u16       trail;             /* 队列底指针 */
    u16       lenmax;            /* 队列长度   */
    CANQUEDATA  *pdata;          /* 消息数组   */
}CANQUEUELIST;


#ifdef CANQUE_USEOS
#include  <ucos_ii.h>
#endif

// 串口初始化结构体
typedef struct canx_t
{
    CAN_TypeDef     * pCanx;
    CANQUEUELIST    * pQueueOut;
    CANQUEUELIST    * pQueueIn;
#ifdef CANQUE_USEOS
    OS_EVENT        * pWrBufSem;
#endif
}CANX;

typedef enum
{
    CANX_BAUD_50K   = 50000,
    CANX_BAUD_100K  = 100000,
    CANX_BAUD_125K  = 125000,
    CANX_BAUD_250K  = 250000,
    CANX_BAUD_500K  = 500000,
    CANX_BAUD_1000K = 1000000,
}CANXBAUD;

/*
*********************************************************************
*  外部引用变量声明
*********************************************************************
*/
CANDRV_EXT   CANX  Can1;
CANDRV_EXT   CANX  Can2;

/*
*********************************************************************
*  外部引用函数声明
*********************************************************************
*/
CANDRV_EXT    void CAN1Init     (CANX *pcan, CANXBAUD baud);
CANDRV_EXT    void CAN2Init     (CANX *pcan, CANXBAUD baud);
CANDRV_EXT    u8   CanTransmit  (CANX *pcan, CANQUEDATA *pdata);
CANDRV_EXT    u8   CanReceive   (CANX *pcan, CANQUEDATA *pdata);


#ifdef __cplusplus
}
#endif

#endif
