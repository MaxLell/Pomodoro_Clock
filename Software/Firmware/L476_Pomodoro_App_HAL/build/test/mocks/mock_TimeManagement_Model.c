#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_TimeManagement_Model.h"


static struct mock_TimeManagement_ModelInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_TimeManagement_Model_Verify(void)
{
}

void mock_TimeManagement_Model_Init(void)
{
  mock_TimeManagement_Model_Destroy();
}

void mock_TimeManagement_Model_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

