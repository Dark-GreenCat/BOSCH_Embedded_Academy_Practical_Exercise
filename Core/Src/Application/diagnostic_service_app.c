#include "diagnostic_service_app.h"
#include "communication_service_app.h"
#include "diagnostic.h"

bool APP_DNS_HandleDiagnosticRequest(uint8_t* request_message, uint8_t* response_message)
{
  switch (request_message[1]) {
  case 0x27:
    return APP_DNS_Plugin_S27_Handler(response_message, request_message);

  case 0x22:
    return APP_DNS_Plugin_S22_Handler(response_message, request_message);

  case 0x2E:
    return APP_DNS_Plugin_S2E_Handler(response_message, request_message);

  default:
    USART3_SendString((uint8_t*) "Service not support\n");
    return false;
  }
}

bool APP_DNS_ConstructDiagnosticRequest(uint8_t* request_message, uint32_t request_size, uint8_t* diagnostic_request, uint32_t diagnostic_size)
{
  memcpy(diagnostic_request, request_message, (request_size < diagnostic_size) ? request_size : diagnostic_size);
  return true;
}

bool APP_DNS_SendDiagnosticRequestToECU(uint8_t* diagnostic_request, uint32_t diagnostic_size)
{
  return APP_CMS_SendMessage(CMS_ECU, diagnostic_request, diagnostic_size);
}

bool APP_DNS_Plugin_S22_Handler(uint8_t* response, uint8_t* request)
{
  SID_22_Practice(response, request);
  return true;
}

bool APP_DNS_Plugin_S27_Handler(uint8_t* response, uint8_t* request)
{
  SID_27_Practice(response, request);
  return true;
}

bool APP_DNS_Plugin_S2E_Handler(uint8_t* response, uint8_t* request)
{
  SID_2E_Practice(response, request);
  return true;
}
