#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "main.h"
#include "tim.h"
#include <stdint.h>

#define AVAILABLE_SERVICE 0x0123
#define INVALID_LENGTH_RESPONSE_CODE 0x13
#define INVALID_DID_RESPONSE_CODE 0x31
#define READ_SID 0x22
#define WRITE_SID 0x2E
#define SESSION_SID 0x27
#define NRC 0x7F
#define ACCESS_DENIED_CODE 0x33
#define WRONG_KEY_RESPONSE_CODE 0x35

void diagnostic_init(void);

void Generate_Seed(uint8_t* seed);
void calculate_key(uint8_t* input, uint8_t* output);
uint8_t compare_key(uint8_t* array1, uint8_t* array2, uint8_t length);

void Negative_Response(uint8_t sid, uint8_t nrc, uint8_t* buffer);

void SID_22_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer);
void SID_2E_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer);
void SID_27_Practice(uint8_t* tx_buffer, uint8_t* rx_buffer);

#endif