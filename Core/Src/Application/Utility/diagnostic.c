#include "diagnostic.h"

uint8_t SEED[4] = { 0x01, 0x08, 0x82, 0x21 };
uint8_t KEY[4] = { 0x00, 0x00, 0x00, 0x00 };

volatile uint8_t SecurityUnlocked = 0;
volatile uint8_t Reject_Key_Process = 0;
uint8_t SeedProvided = 0;
uint32_t StdIDData;

void Generate_Seed(uint8_t* seed)
{
  srand((unsigned int) TimeStamp);
  seed[0] = rand() % 256;
  seed[1] = rand() % 256;
  seed[2] = rand() % 256;
  seed[3] = rand() % 256;
}

void calculate_key(uint8_t* input, uint8_t* output)
{
  output[0] = input[0] ^ input[1];
  output[1] = input[1] + input[2];
  output[2] = input[2] ^ input[3];
  output[3] = input[3] + input[0];
}

uint8_t compare_key(uint8_t* array1, uint8_t* array2, uint8_t length)
{
  for (uint8_t i = 0; i < length; i++) {
    if (array1[i] != array2[i]) {
      return 0;
    }
  }
  return 1;
}

void Negative_Response(uint8_t sid, uint8_t nrc, uint8_t* buffer)
{
  buffer[0] = 0x03;
  buffer[1] = NRC;
  buffer[2] = sid;
  buffer[3] = nrc;
  for (int i = 4; i < 8; i++) {
    buffer[i] = 0x55;
  }
}

void SID_22_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer)
{
  delay(100);
  if (rx_buffer[0] != 3) // Invalid length
  {
    Negative_Response(READ_SID, INVALID_LENGTH_RESPONSE_CODE, tx_buffer);
  } else if (((rx_buffer[2] << 8) | rx_buffer[3]) != AVAILABLE_SERVICE) // INVALID DID
  {
    Negative_Response(READ_SID, INVALID_DID_RESPONSE_CODE, tx_buffer);
  } else // CAN2 Receive Correct message
  {
    tx_buffer[0] = 0x05;
    tx_buffer[1] = rx_buffer[1] + 0x40;
    tx_buffer[2] = rx_buffer[2];
    tx_buffer[3] = rx_buffer[3];
    tx_buffer[4] = StdIDData >> 8;
    tx_buffer[5] = StdIDData & 0xFF;
    tx_buffer[6] = 0x55;
    tx_buffer[7] = 0x55;
  }
  if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, tx_buffer, &CAN2_pTxMailbox)
      != HAL_OK) {
    Error_Handler();
  }
  delay(100);
}
void SID_27_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer)
{
  delay(100);
  if (Reject_Key_Process)
    return;
  switch (rx_buffer[2]) {
  case 0x01:
    if (rx_buffer[0] != 2) {
      Negative_Response(SESSION_SID, INVALID_LENGTH_RESPONSE_CODE, tx_buffer);
    } else {
      Generate_Seed(SEED);
      tx_buffer[0] = 0x06;
      tx_buffer[1] = rx_buffer[1] + 0x40;
      tx_buffer[2] = 0x01;
      for (int i = 3; i < 7; i++) {
        tx_buffer[i] = SEED[i - 3];
      }
      tx_buffer[7] = 0x55;
      calculate_key(SEED, KEY);
      SeedProvided = 1;
    }
    break;
  case 0x02:
    if (rx_buffer[0] != 6) {
      Negative_Response(SESSION_SID, INVALID_LENGTH_RESPONSE_CODE, tx_buffer);
    } else if (!compare_key(KEY, &rx_buffer[3], 4)) {
      HAL_TIM_Base_Start_IT(&htim2);
      Reject_Key_Process = 1;
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
      Negative_Response(SESSION_SID, WRONG_KEY_RESPONSE_CODE, tx_buffer);
    } else if (SeedProvided && !SecurityUnlocked) {
      HAL_TIM_Base_Start_IT(&htim3);
      SecurityUnlocked = 1;
      HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

      USART3_SendString((uint8_t*) "Session Unlocked\n");

      tx_buffer[0] = 0x02;
      tx_buffer[1] = rx_buffer[1] + 0x40;
      tx_buffer[2] = 0x02;
      for (int i = 3; i < 8; i++) {
        tx_buffer[i] = 0x55;
      }
      SeedProvided = 0;
    } else {
      return;
    }
    break;
  default:
    if (rx_buffer[0]) { // Case "01 27"
      Negative_Response(SESSION_SID, INVALID_LENGTH_RESPONSE_CODE, tx_buffer);
      break;
    } else
      return;
  }
  if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, tx_buffer, &CAN2_pTxMailbox)
      != HAL_OK) {
    Error_Handler();
  }
  delay(100);
}
void SID_2E_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer)
{
  delay(100);
  if (!SecurityUnlocked) {
    Negative_Response(WRITE_SID, ACCESS_DENIED_CODE, tx_buffer);
  } else if (rx_buffer[0] < 5) {
    Negative_Response(WRITE_SID, INVALID_LENGTH_RESPONSE_CODE, tx_buffer);
  } else if (((rx_buffer[2] << 8) | rx_buffer[3]) != AVAILABLE_SERVICE) // INVALID DID
  {
    Negative_Response(WRITE_SID, INVALID_DID_RESPONSE_CODE, tx_buffer);
  } else {
    StdIDData = ((((uint32_t) rx_buffer[4]) << 8) | (rx_buffer[5])) & 0x7FF;
    tx_buffer[0] = 0x03;
    tx_buffer[1] = rx_buffer[1] + 0x40;
    tx_buffer[2] = rx_buffer[2];
    tx_buffer[3] = rx_buffer[3];
    for (int i = 4; i < 8; i++) {
      tx_buffer[i] = 0x55;
    }
  }
  if (HAL_CAN_AddTxMessage(&hcan2, &CAN2_pHeader, tx_buffer, &CAN2_pTxMailbox)
      != HAL_OK) {
    Error_Handler();
  }
  delay(100);
}