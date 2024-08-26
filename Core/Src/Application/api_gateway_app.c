#include "api_gateway_app.h"
#include "communication_service_app.h"
#include "diagnostic_service_app.h"
#include "user_interface_service_app.h"

#include "main.h"
#include "can.h"

bool APP_GATEWAY_GetRequestFromTester(uint8_t* request_message, uint32_t size) {
    return APP_CMS_GetMessage(CMS_TESTER, request_message, size);
}

bool APP_GATEWAY_HandleRequestOfTester(uint8_t* request_message, uint8_t* response_message) {
    return APP_DNS_HandleDiagnosticRequest(request_message, response_message);
}

bool APP_GATEWAY_SendResponseToTester(uint8_t* response_message, uint32_t size) {
    return APP_CMS_SendMessage(CMS_TESTER, response_message, size);
}

bool APP_GATEWAY_GetRequestFromUser(uint8_t* request_message, uint32_t size) {
    if (NumBytesReq == 0) return false;

    delay(100);
    read_from_buffer(REQ_BUFFER, (NumBytesReq < size) ? NumBytesReq : size, request_message);
    NumBytesReq = 0;
    return true;
}

bool APP_GATEWAY_SendRequestToECU(uint8_t* request_message, uint32_t size) {
    uint8_t diagnostic_request[8];
    APP_DNS_ConstructDiagnosticRequest(request_message, size, diagnostic_request, sizeof(diagnostic_request));
    return APP_DNS_SendDiagnosticRequestToECU(diagnostic_request, sizeof(diagnostic_request));
}

bool APP_GATEWAY_GetResponseFromECU(uint8_t* response_message, uint32_t size) {
    return APP_CMS_GetMessage(CMS_ECU, response_message, size);
}

void APP_GATEWAY_SendLogToUser(uint8_t* log) {
    APP_UIS_SendLogToUser(log);
}

