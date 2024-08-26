#ifndef API_GATEWAY_APP_H
#define API_GATEWAY_APP_H

#include <stdbool.h>
#include <stdint.h>

bool APP_GATEWAY_GetRequestFromTester(uint8_t* request_message, uint32_t size);
bool APP_GATEWAY_HandleRequestOfTester(uint8_t* request_message, uint8_t* response_message);
bool APP_GATEWAY_SendResponseToTester(uint8_t* response_message, uint32_t size);

bool APP_GATEWAY_GetRequestFromUser(uint8_t* request_message, uint32_t size);
bool APP_GATEWAY_SendRequestToECU(uint8_t* request_message, uint32_t size);
bool APP_GATEWAY_GetResponseFromECU(uint8_t* response_message, uint32_t size);

void APP_GATEWAY_SendLogToUser(uint8_t* log);

#endif