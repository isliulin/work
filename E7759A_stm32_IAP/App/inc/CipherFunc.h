/*
**********************************************************************************************************
*  Copyright (C), 2009-2012, 合众思壮西安研发中心
*
*  项目名称： E6202
*  
*  文件名称:  CipherFunc.h
*
*  文件描述： 加密解密
*             
*             
*  创 建 者: 皇海明
*
*  创建日期：2013-03-20 
*
*  版 本 号：V1.0
*
*  修改记录： 
*             
*      1. 日    期： 
*         修 改 人： 
*         所作修改： 
*      2. ...
**********************************************************************************************************
*/
#ifndef __CIPHERFUNC_H
#define __CIPHERFUNC_H

#ifdef __cplusplus
extern "C" {
#endif
	
#ifdef  CIPHERFUNC_GLB
#define CIPHERFUNC_EXTERN
#else
#define CIPHERFUNC_EXTERN   extern
#endif

	


/*
*********************************************************************
*  全局宏定义
*********************************************************************
*/
 



/*
*********************************************************************
*  类、结构体类型定义
*********************************************************************
*/


/*
*********************************************************************
*  外部引用变量声明
*********************************************************************
*/

/*
*********************************************************************
*  外部引用函数声明
*********************************************************************
*/
CIPHERFUNC_EXTERN char CmpCipher(void);




#ifdef __cplusplus
}
#endif

#endif /* __CIPHERFUNC_H */

