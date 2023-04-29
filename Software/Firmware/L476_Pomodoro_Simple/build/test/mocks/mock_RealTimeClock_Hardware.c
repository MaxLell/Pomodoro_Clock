/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_RealTimeClock_Hardware.h"

static const char* CMockString_RealTimeClockHW_getTimeAndDate = "RealTimeClockHW_getTimeAndDate";
static const char* CMockString_in_pTimeAndDate = "in_pTimeAndDate";

typedef struct _CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  status_t ReturnVal;
  int CallOrder;
  RealTimeClock_TimeAndDate_t* Expected_in_pTimeAndDate;
  char ReturnThruPtr_in_pTimeAndDate_Used;
  RealTimeClock_TimeAndDate_t* ReturnThruPtr_in_pTimeAndDate_Val;
  size_t ReturnThruPtr_in_pTimeAndDate_Size;
  char IgnoreArg_in_pTimeAndDate;

} CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE;

static struct mock_RealTimeClock_HardwareInstance
{
  char RealTimeClockHW_getTimeAndDate_IgnoreBool;
  status_t RealTimeClockHW_getTimeAndDate_FinalReturn;
  char RealTimeClockHW_getTimeAndDate_CallbackBool;
  CMOCK_RealTimeClockHW_getTimeAndDate_CALLBACK RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer;
  int RealTimeClockHW_getTimeAndDate_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE RealTimeClockHW_getTimeAndDate_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_RealTimeClock_Hardware_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.RealTimeClockHW_getTimeAndDate_CallInstance;
  if (Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_RealTimeClockHW_getTimeAndDate);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_RealTimeClock_Hardware_Init(void)
{
  mock_RealTimeClock_Hardware_Destroy();
}

void mock_RealTimeClock_Hardware_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

status_t RealTimeClockHW_getTimeAndDate(RealTimeClock_TimeAndDate_t* in_pTimeAndDate)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_RealTimeClockHW_getTimeAndDate);
  cmock_call_instance = (CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.RealTimeClockHW_getTimeAndDate_CallInstance);
  Mock.RealTimeClockHW_getTimeAndDate_CallInstance = CMock_Guts_MemNext(Mock.RealTimeClockHW_getTimeAndDate_CallInstance);
  if (Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.RealTimeClockHW_getTimeAndDate_FinalReturn;
    memcpy((void*)(&Mock.RealTimeClockHW_getTimeAndDate_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(status_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.RealTimeClockHW_getTimeAndDate_CallbackBool &&
      Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer != NULL)
  {
    status_t cmock_cb_ret = Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer(in_pTimeAndDate, Mock.RealTimeClockHW_getTimeAndDate_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (!cmock_call_instance->IgnoreArg_in_pTimeAndDate)
  {
    UNITY_SET_DETAILS(CMockString_RealTimeClockHW_getTimeAndDate,CMockString_in_pTimeAndDate);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_in_pTimeAndDate), (void*)(in_pTimeAndDate), sizeof(RealTimeClock_TimeAndDate_t), cmock_line, CMockStringMismatch);
  }
  if (Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer(in_pTimeAndDate, Mock.RealTimeClockHW_getTimeAndDate_CallbackCalls++);
  }
  if (cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Used)
  {
    UNITY_TEST_ASSERT_NOT_NULL(in_pTimeAndDate, cmock_line, CMockStringPtrIsNULL);
    memcpy((void*)in_pTimeAndDate, (void*)cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Val,
      cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Size);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_RealTimeClockHW_getTimeAndDate(CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance, RealTimeClock_TimeAndDate_t* in_pTimeAndDate);
void CMockExpectParameters_RealTimeClockHW_getTimeAndDate(CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance, RealTimeClock_TimeAndDate_t* in_pTimeAndDate)
{
  cmock_call_instance->Expected_in_pTimeAndDate = in_pTimeAndDate;
  cmock_call_instance->IgnoreArg_in_pTimeAndDate = 0;
  cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Used = 0;
}

void RealTimeClockHW_getTimeAndDate_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE));
  CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance = (CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.RealTimeClockHW_getTimeAndDate_CallInstance = CMock_Guts_MemChain(Mock.RealTimeClockHW_getTimeAndDate_CallInstance, cmock_guts_index);
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)1;
}

void RealTimeClockHW_getTimeAndDate_CMockStopIgnore(void)
{
  if(Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool)
    Mock.RealTimeClockHW_getTimeAndDate_CallInstance = CMock_Guts_MemNext(Mock.RealTimeClockHW_getTimeAndDate_CallInstance);
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)0;
}

void RealTimeClockHW_getTimeAndDate_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, RealTimeClock_TimeAndDate_t* in_pTimeAndDate, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE));
  CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance = (CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.RealTimeClockHW_getTimeAndDate_CallInstance = CMock_Guts_MemChain(Mock.RealTimeClockHW_getTimeAndDate_CallInstance, cmock_guts_index);
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_RealTimeClockHW_getTimeAndDate(cmock_call_instance, in_pTimeAndDate);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(status_t[sizeof(cmock_to_return) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
}

void RealTimeClockHW_getTimeAndDate_AddCallback(CMOCK_RealTimeClockHW_getTimeAndDate_CALLBACK Callback)
{
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)0;
  Mock.RealTimeClockHW_getTimeAndDate_CallbackBool = (char)1;
  Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer = Callback;
}

void RealTimeClockHW_getTimeAndDate_Stub(CMOCK_RealTimeClockHW_getTimeAndDate_CALLBACK Callback)
{
  Mock.RealTimeClockHW_getTimeAndDate_IgnoreBool = (char)0;
  Mock.RealTimeClockHW_getTimeAndDate_CallbackBool = (char)0;
  Mock.RealTimeClockHW_getTimeAndDate_CallbackFunctionPointer = Callback;
}

void RealTimeClockHW_getTimeAndDate_CMockReturnMemThruPtr_in_pTimeAndDate(UNITY_LINE_TYPE cmock_line, RealTimeClock_TimeAndDate_t* in_pTimeAndDate, size_t cmock_size)
{
  CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance = (CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.RealTimeClockHW_getTimeAndDate_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringPtrPreExp);
  cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Used = 1;
  cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Val = in_pTimeAndDate;
  cmock_call_instance->ReturnThruPtr_in_pTimeAndDate_Size = cmock_size;
}

void RealTimeClockHW_getTimeAndDate_CMockIgnoreArg_in_pTimeAndDate(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE* cmock_call_instance = (CMOCK_RealTimeClockHW_getTimeAndDate_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.RealTimeClockHW_getTimeAndDate_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_in_pTimeAndDate = 1;
}
