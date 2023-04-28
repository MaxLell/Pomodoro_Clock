#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_Buzzer_Hardware.h"


static struct mock_Buzzer_HardwareInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_Buzzer_Hardware_Verify(void)
{
}

void mock_Buzzer_Hardware_Init(void)
{
  mock_Buzzer_Hardware_Destroy();
}

void mock_Buzzer_Hardware_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

