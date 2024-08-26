#include "communication_service_app.h"
#include "can.h"

bool APP_CMS_GetMessage(CMS_Target_t target, uint8_t* message, uint32_t size)
{
  if (target == CMS_ECU) {
    if (CAN1Received == 0)
      return false;

    uint32_t actual_size = sizeof(CAN2_DATA_RX);
    memcpy(message, CAN1_DATA_RX, (actual_size < size) ? actual_size : size);
    CAN1Received = 0;
    return true;
  }

  if (target == CMS_TESTER) {
    if (CAN2Received == 0)
      return false;

    uint32_t actual_size = sizeof(CAN2_DATA_RX);
    memcpy(message, CAN2_DATA_RX, (actual_size < size) ? actual_size : size);
    CAN2Received = 0;
    return true;
  }

  return false;
}

bool APP_CMS_SendMessage(CMS_Target_t target, uint8_t* message, uint32_t size)
{
  if (target == CMS_ECU) {
    uint32_t actual_size = sizeof(CAN1_DATA_TX);
    memcpy(CAN1_DATA_TX, message, (actual_size < size) ? actual_size : size);
    CAN1_Send();
    APP_Delay(100);
    return true;
  }

  if (target == CMS_TESTER) {
    if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, message, &CAN2_pTxMailbox)
        != HAL_OK) {
      Error_Handler();
      return false;
    }
    APP_Delay(100);
    return true;
  }

  return false;
}
