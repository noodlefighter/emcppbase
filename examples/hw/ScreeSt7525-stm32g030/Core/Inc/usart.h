/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define		DEBUG_RX_MAX		128
#define		DEBUG_TX_MAX		128
#define		DEBUG_RX_BUF		USART1_RX_BUF	//Debug���ջ���
#define		DEBUG_RX_COUNT		Usart1RXCount	//Debug��������
#define 	DEBUG_RX_FLAG		Usart1RXFlag	//Debug������ɱ�־

#define		CMD_RX_MAX			1664
#define		CMD_TX_MAX			128
#define		CMD_RX_BUF			USART2_RX_BUF	//Debug���ջ���
#define		CMD_RX_COUNT		Usart2RXCount	//Debug��������
#define 	CMD_RX_FLAG			Usart2RXFlag	//Debug������ɱ�־
/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */
extern uint8_t Usart1RxBuffer[DEBUG_RX_MAX];
extern uint8_t Usart2RxBuffer[CMD_RX_MAX];	//DMA���ջ���

extern uint8_t USART1_RX_BUF[DEBUG_RX_MAX]; 	      //���ͻ���,���256�ֽ�
extern uint8_t USART2_RX_BUF[CMD_RX_MAX];

extern uint16_t Usart1RXCount;
extern uint8_t Usart1RXFlag;

extern uint16_t Usart2RXCount;
extern uint8_t Usart2RXFlag;
/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void u1_printf(char* fmt,...);
void TaskForObserUsart1Rec(void);

void u2_printf(char* fmt,...);


void CMDSendData(uint8_t *buf, uint16_t len);

void ClearDebugBuff(void);
void ClearCmdBuff(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
