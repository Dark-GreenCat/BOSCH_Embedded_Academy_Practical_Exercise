#ifndef COMMUNICATION_SERVICE_APP_H
#define COMMUNICATION_SERVICE_APP_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
  CMS_TESTER,
  CMS_ECU
} CMS_Target_t;

bool APP_CMS_GetMessage(CMS_Target_t target, uint8_t* message, uint32_t size);
bool APP_CMS_SendMessage(CMS_Target_t target, uint8_t* message, uint32_t size);

#endif