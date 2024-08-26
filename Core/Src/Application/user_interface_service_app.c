#include "user_interface_service_app.h"
#include "usart.h"

void APP_UIS_SendLogToUser(uint8_t* log) {
    USART3_SendString(log);
}