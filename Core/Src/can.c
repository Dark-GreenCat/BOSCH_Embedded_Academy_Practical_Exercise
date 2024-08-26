/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    can.c
 * @brief   This file provides code for the configuration
 *          of the CAN instances.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
volatile uint8_t CAN1Received = 0;
volatile uint8_t CAN2Received = 0;

uint8_t CAN1_DATA_TX[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t CAN1_DATA_RX[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t CAN2_DATA_TX[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t CAN2_DATA_RX[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 21;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */
}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 21;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_12TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */
}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED = 0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = { 0 };
  if (canHandle->Instance == CAN1) {
    /* USER CODE BEGIN CAN1_MspInit 0 */

    /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if (HAL_RCC_CAN1_CLK_ENABLED == 1) {
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    /* USER CODE BEGIN CAN1_MspInit 1 */

    /* USER CODE END CAN1_MspInit 1 */
  } else if (canHandle->Instance == CAN2) {
    /* USER CODE BEGIN CAN2_MspInit 0 */

    /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if (HAL_RCC_CAN1_CLK_ENABLED == 1) {
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
    /* USER CODE BEGIN CAN2_MspInit 1 */

    /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if (canHandle->Instance == CAN1) {
    /* USER CODE BEGIN CAN1_MspDeInit 0 */

    /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if (HAL_RCC_CAN1_CLK_ENABLED == 0) {
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PA11     ------> CAN1_RX
    PA12     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11 | GPIO_PIN_12);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    /* USER CODE BEGIN CAN1_MspDeInit 1 */

    /* USER CODE END CAN1_MspDeInit 1 */
  } else if (canHandle->Instance == CAN2) {
    /* USER CODE BEGIN CAN2_MspDeInit 0 */

    /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if (HAL_RCC_CAN1_CLK_ENABLED == 0) {
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB5     ------> CAN2_RX
    PB6     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_5 | GPIO_PIN_6);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    /* USER CODE BEGIN CAN2_MspDeInit 1 */

    /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
  HAL_StatusTypeDef ret;
  if (hcan == &hcan1) {
    ret = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN1_pHeaderRx,
        CAN1_DATA_RX);
    if (ret != HAL_OK) {
      Error_Handler();
    }
    CAN1Received = 1;
    return;
  }
  if (hcan == &hcan2) {
    ret = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &CAN2_pHeaderRx,
        CAN2_DATA_RX);
    if (ret != HAL_OK) {
      Error_Handler();
    }
    CAN2Received = 1;
    return;
  }
}

void MX_CAN1_Setup()
{
  HAL_CAN_ConfigFilter(&hcan1, &CAN1_sFilterConfig);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void MX_CAN2_Setup()
{
  HAL_CAN_ConfigFilter(&hcan2, &CAN2_sFilterConfig);
  HAL_CAN_Start(&hcan2);
  HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CAN1CommSetup()
{
  CAN1_pHeader.IDE = CAN_ID_STD;
  CAN1_pHeader.StdId = 0x078;
  CAN1_pHeader.RTR = CAN_RTR_DATA;
  CAN1_pHeader.DLC = 8;
  CAN1_sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  CAN1_sFilterConfig.FilterBank = 14;
  CAN1_sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN1_sFilterConfig.FilterIdHigh = 0x0A2 << 5;
  CAN1_sFilterConfig.FilterIdLow = 0;
  CAN1_sFilterConfig.FilterMaskIdHigh = 0x0A2 << 5;
  CAN1_sFilterConfig.FilterMaskIdLow = 0;
  CAN1_sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN1_sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  CAN1_sFilterConfig.SlaveStartFilterBank = 16;
  HAL_CAN_ConfigFilter(&hcan1, &CAN1_sFilterConfig);
}

void CAN2CommSetup()
{
  CAN2_pHeader.IDE = CAN_ID_STD;
  CAN2_pHeader.StdId = 0x0A2;
  CAN2_pHeader.RTR = CAN_RTR_DATA;
  CAN2_pHeader.DLC = 8;
  CAN2_sFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
  CAN2_sFilterConfig.FilterBank = 18;
  CAN2_sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  CAN2_sFilterConfig.FilterIdHigh = CAN1_pHeader.StdId << 5;
  CAN2_sFilterConfig.FilterIdLow = 0;
  CAN2_sFilterConfig.FilterMaskIdHigh = CAN1_pHeader.StdId << 5;
  CAN2_sFilterConfig.FilterMaskIdLow = 0;
  CAN2_sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  CAN2_sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  HAL_CAN_ConfigFilter(&hcan2, &CAN2_sFilterConfig);
}

void read_from_buffer(uint8_t* req_buffer, uint16_t len, uint8_t* data_tx)
{
  data_tx[0] = len;
  uint8_t i;
  for (i = 0; i < len; i++) {
    data_tx[i + 1] = req_buffer[i];
  }
  while (i <= 7) {
    i++;
    data_tx[i] = 0x55;
  }
}

void CAN1_Send()
{
  PrintCANLog(CAN1_pHeader.StdId, CAN1_DATA_TX);
  if (HAL_CAN_AddTxMessage(&hcan1, &CAN1_pHeader, CAN1_DATA_TX,
          &CAN1_pTxMailbox)
      != HAL_OK) {
    Error_Handler();
  }
}

void CAN2_Send()
{
  PrintCANLog(CAN2_pHeader.StdId, CAN2_DATA_TX);
  if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, CAN2_DATA_TX,
          &CAN2_pTxMailbox)
      != HAL_OK) {
    Error_Handler();
  }
}
/* USER CODE END 1 */
