/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_Button_Hardware.h"

static const char* CMockString_Button_Hardware_init = "Button_Hardware_init";
static const char* CMockString_Button_Hardware_wasPressed = "Button_Hardware_wasPressed";

typedef struct _CMOCK_Button_Hardware_init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  int CallOrder;

} CMOCK_Button_Hardware_init_CALL_INSTANCE;

typedef struct _CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  BOOL ReturnVal;
  int CallOrder;

} CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE;

static struct mock_Button_HardwareInstance
{
  char Button_Hardware_init_IgnoreBool;
  char Button_Hardware_init_CallbackBool;
  CMOCK_Button_Hardware_init_CALLBACK Button_Hardware_init_CallbackFunctionPointer;
  int Button_Hardware_init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Button_Hardware_init_CallInstance;
  char Button_Hardware_wasPressed_IgnoreBool;
  BOOL Button_Hardware_wasPressed_FinalReturn;
  char Button_Hardware_wasPressed_CallbackBool;
  CMOCK_Button_Hardware_wasPressed_CALLBACK Button_Hardware_wasPressed_CallbackFunctionPointer;
  int Button_Hardware_wasPressed_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE Button_Hardware_wasPressed_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_Button_Hardware_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.Button_Hardware_init_CallInstance;
  if (Mock.Button_Hardware_init_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_Button_Hardware_init);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.Button_Hardware_init_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.Button_Hardware_wasPressed_CallInstance;
  if (Mock.Button_Hardware_wasPressed_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_Button_Hardware_wasPressed);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.Button_Hardware_wasPressed_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_Button_Hardware_Init(void)
{
  mock_Button_Hardware_Destroy();
}

void mock_Button_Hardware_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

void Button_Hardware_init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_Button_Hardware_init_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_Button_Hardware_init);
  cmock_call_instance = (CMOCK_Button_Hardware_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Button_Hardware_init_CallInstance);
  Mock.Button_Hardware_init_CallInstance = CMock_Guts_MemNext(Mock.Button_Hardware_init_CallInstance);
  if (Mock.Button_Hardware_init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    return;
  }
  if (!Mock.Button_Hardware_init_CallbackBool &&
      Mock.Button_Hardware_init_CallbackFunctionPointer != NULL)
  {
    Mock.Button_Hardware_init_CallbackFunctionPointer(Mock.Button_Hardware_init_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (Mock.Button_Hardware_init_CallbackFunctionPointer != NULL)
  {
    Mock.Button_Hardware_init_CallbackFunctionPointer(Mock.Button_Hardware_init_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
}

void Button_Hardware_init_CMockIgnore(void)
{
  Mock.Button_Hardware_init_IgnoreBool = (char)1;
}

void Button_Hardware_init_CMockStopIgnore(void)
{
  Mock.Button_Hardware_init_IgnoreBool = (char)0;
}

void Button_Hardware_init_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Button_Hardware_init_CALL_INSTANCE));
  CMOCK_Button_Hardware_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_Button_Hardware_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Button_Hardware_init_CallInstance = CMock_Guts_MemChain(Mock.Button_Hardware_init_CallInstance, cmock_guts_index);
  Mock.Button_Hardware_init_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
}

void Button_Hardware_init_AddCallback(CMOCK_Button_Hardware_init_CALLBACK Callback)
{
  Mock.Button_Hardware_init_IgnoreBool = (char)0;
  Mock.Button_Hardware_init_CallbackBool = (char)1;
  Mock.Button_Hardware_init_CallbackFunctionPointer = Callback;
}

void Button_Hardware_init_Stub(CMOCK_Button_Hardware_init_CALLBACK Callback)
{
  Mock.Button_Hardware_init_IgnoreBool = (char)0;
  Mock.Button_Hardware_init_CallbackBool = (char)0;
  Mock.Button_Hardware_init_CallbackFunctionPointer = Callback;
}

BOOL Button_Hardware_wasPressed(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_Button_Hardware_wasPressed);
  cmock_call_instance = (CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.Button_Hardware_wasPressed_CallInstance);
  Mock.Button_Hardware_wasPressed_CallInstance = CMock_Guts_MemNext(Mock.Button_Hardware_wasPressed_CallInstance);
  if (Mock.Button_Hardware_wasPressed_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.Button_Hardware_wasPressed_FinalReturn;
    Mock.Button_Hardware_wasPressed_FinalReturn = cmock_call_instance->ReturnVal;
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.Button_Hardware_wasPressed_CallbackBool &&
      Mock.Button_Hardware_wasPressed_CallbackFunctionPointer != NULL)
  {
    BOOL cmock_cb_ret = Mock.Button_Hardware_wasPressed_CallbackFunctionPointer(Mock.Button_Hardware_wasPressed_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (Mock.Button_Hardware_wasPressed_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.Button_Hardware_wasPressed_CallbackFunctionPointer(Mock.Button_Hardware_wasPressed_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void Button_Hardware_wasPressed_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE));
  CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Button_Hardware_wasPressed_CallInstance = CMock_Guts_MemChain(Mock.Button_Hardware_wasPressed_CallInstance, cmock_guts_index);
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)1;
}

void Button_Hardware_wasPressed_CMockStopIgnore(void)
{
  if(Mock.Button_Hardware_wasPressed_IgnoreBool)
    Mock.Button_Hardware_wasPressed_CallInstance = CMock_Guts_MemNext(Mock.Button_Hardware_wasPressed_CallInstance);
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)0;
}

void Button_Hardware_wasPressed_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE));
  CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE* cmock_call_instance = (CMOCK_Button_Hardware_wasPressed_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.Button_Hardware_wasPressed_CallInstance = CMock_Guts_MemChain(Mock.Button_Hardware_wasPressed_CallInstance, cmock_guts_index);
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  cmock_call_instance->ReturnVal = cmock_to_return;
}

void Button_Hardware_wasPressed_AddCallback(CMOCK_Button_Hardware_wasPressed_CALLBACK Callback)
{
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)0;
  Mock.Button_Hardware_wasPressed_CallbackBool = (char)1;
  Mock.Button_Hardware_wasPressed_CallbackFunctionPointer = Callback;
}

void Button_Hardware_wasPressed_Stub(CMOCK_Button_Hardware_wasPressed_CALLBACK Callback)
{
  Mock.Button_Hardware_wasPressed_IgnoreBool = (char)0;
  Mock.Button_Hardware_wasPressed_CallbackBool = (char)0;
  Mock.Button_Hardware_wasPressed_CallbackFunctionPointer = Callback;
}

