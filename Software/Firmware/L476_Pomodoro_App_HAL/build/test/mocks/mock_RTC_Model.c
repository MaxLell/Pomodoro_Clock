#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_RTC_Model.h"


static struct mock_RTC_ModelInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_RTC_Model_Verify(void)
{
}

void mock_RTC_Model_Init(void)
{
  mock_RTC_Model_Destroy();
}

void mock_RTC_Model_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

