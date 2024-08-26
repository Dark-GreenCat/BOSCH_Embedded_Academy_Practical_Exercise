#ifndef DIAGNOSTIC_SERVICE_APP_H
#define DIAGNOSTIC_SERVICE_APP_H

#include <stdint.h>
#include <stdbool.h>

bool APP_DNS_HandleDiagnosticRequest(uint8_t* request_message, uint8_t* response_message);
bool APP_DNS_ConstructDiagnosticRequest(uint8_t* request_message, uint32_t request_size, uint8_t* diagnostic_request, uint32_t diagnostic_size);
bool APP_DNS_SendDiagnosticRequestToECU(uint8_t* diagnostic_request, uint32_t diagnostic_size);

bool APP_DNS_Plugin_S22_Handler(uint8_t* response, uint8_t* request);
bool APP_DNS_Plugin_S27_Handler(uint8_t* response, uint8_t* request);
bool APP_DNS_Plugin_S2E_Handler(uint8_t* response, uint8_t* request);

#endif
