/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "mock_MessageBroker.h"

static const char* CMockString_MessageBroker_init = "MessageBroker_init";
static const char* CMockString_MessageBroker_publish = "MessageBroker_publish";
static const char* CMockString_MessageBroker_subscribe = "MessageBroker_subscribe";
static const char* CMockString_in_eMsgTopic = "in_eMsgTopic";
static const char* CMockString_in_p32FunctionCallback = "in_p32FunctionCallback";
static const char* CMockString_in_tMessage = "in_tMessage";

typedef struct _CMOCK_MessageBroker_init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  status_t ReturnVal;
  int CallOrder;

} CMOCK_MessageBroker_init_CALL_INSTANCE;

typedef struct _CMOCK_MessageBroker_subscribe_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  status_t ReturnVal;
  int CallOrder;
  MessageTopics_e Expected_in_eMsgTopic;
  Module_msgCallback_t Expected_in_p32FunctionCallback;
  char IgnoreArg_in_eMsgTopic;
  char IgnoreArg_in_p32FunctionCallback;

} CMOCK_MessageBroker_subscribe_CALL_INSTANCE;

typedef struct _CMOCK_MessageBroker_publish_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  status_t ReturnVal;
  int CallOrder;
  MessageBroker_message_t Expected_in_tMessage;
  char IgnoreArg_in_tMessage;

} CMOCK_MessageBroker_publish_CALL_INSTANCE;

static struct mock_MessageBrokerInstance
{
  char MessageBroker_init_IgnoreBool;
  status_t MessageBroker_init_FinalReturn;
  char MessageBroker_init_CallbackBool;
  CMOCK_MessageBroker_init_CALLBACK MessageBroker_init_CallbackFunctionPointer;
  int MessageBroker_init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE MessageBroker_init_CallInstance;
  char MessageBroker_subscribe_IgnoreBool;
  status_t MessageBroker_subscribe_FinalReturn;
  char MessageBroker_subscribe_CallbackBool;
  CMOCK_MessageBroker_subscribe_CALLBACK MessageBroker_subscribe_CallbackFunctionPointer;
  int MessageBroker_subscribe_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE MessageBroker_subscribe_CallInstance;
  char MessageBroker_publish_IgnoreBool;
  status_t MessageBroker_publish_FinalReturn;
  char MessageBroker_publish_CallbackBool;
  CMOCK_MessageBroker_publish_CALLBACK MessageBroker_publish_CallbackFunctionPointer;
  int MessageBroker_publish_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE MessageBroker_publish_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_MessageBroker_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.MessageBroker_init_CallInstance;
  if (Mock.MessageBroker_init_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_MessageBroker_init);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.MessageBroker_init_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.MessageBroker_subscribe_CallInstance;
  if (Mock.MessageBroker_subscribe_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_MessageBroker_subscribe);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.MessageBroker_subscribe_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
  call_instance = Mock.MessageBroker_publish_CallInstance;
  if (Mock.MessageBroker_publish_IgnoreBool)
    call_instance = CMOCK_GUTS_NONE;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_MessageBroker_publish);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  if (Mock.MessageBroker_publish_CallbackFunctionPointer != NULL)
  {
    call_instance = CMOCK_GUTS_NONE;
    (void)call_instance;
  }
}

void mock_MessageBroker_Init(void)
{
  mock_MessageBroker_Destroy();
}

void mock_MessageBroker_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

status_t MessageBroker_init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MessageBroker_init_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_MessageBroker_init);
  cmock_call_instance = (CMOCK_MessageBroker_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.MessageBroker_init_CallInstance);
  Mock.MessageBroker_init_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_init_CallInstance);
  if (Mock.MessageBroker_init_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.MessageBroker_init_FinalReturn;
    memcpy((void*)(&Mock.MessageBroker_init_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(status_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.MessageBroker_init_CallbackBool &&
      Mock.MessageBroker_init_CallbackFunctionPointer != NULL)
  {
    status_t cmock_cb_ret = Mock.MessageBroker_init_CallbackFunctionPointer(Mock.MessageBroker_init_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (Mock.MessageBroker_init_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.MessageBroker_init_CallbackFunctionPointer(Mock.MessageBroker_init_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void MessageBroker_init_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_init_CALL_INSTANCE));
  CMOCK_MessageBroker_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_init_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_init_CallInstance, cmock_guts_index);
  Mock.MessageBroker_init_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.MessageBroker_init_IgnoreBool = (char)1;
}

void MessageBroker_init_CMockStopIgnore(void)
{
  if(Mock.MessageBroker_init_IgnoreBool)
    Mock.MessageBroker_init_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_init_CallInstance);
  Mock.MessageBroker_init_IgnoreBool = (char)0;
}

void MessageBroker_init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_init_CALL_INSTANCE));
  CMOCK_MessageBroker_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_init_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_init_CallInstance, cmock_guts_index);
  Mock.MessageBroker_init_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(status_t[sizeof(cmock_to_return) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
}

void MessageBroker_init_AddCallback(CMOCK_MessageBroker_init_CALLBACK Callback)
{
  Mock.MessageBroker_init_IgnoreBool = (char)0;
  Mock.MessageBroker_init_CallbackBool = (char)1;
  Mock.MessageBroker_init_CallbackFunctionPointer = Callback;
}

void MessageBroker_init_Stub(CMOCK_MessageBroker_init_CALLBACK Callback)
{
  Mock.MessageBroker_init_IgnoreBool = (char)0;
  Mock.MessageBroker_init_CallbackBool = (char)0;
  Mock.MessageBroker_init_CallbackFunctionPointer = Callback;
}

status_t MessageBroker_subscribe(MessageTopics_e in_eMsgTopic, Module_msgCallback_t in_p32FunctionCallback)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_MessageBroker_subscribe);
  cmock_call_instance = (CMOCK_MessageBroker_subscribe_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.MessageBroker_subscribe_CallInstance);
  Mock.MessageBroker_subscribe_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_subscribe_CallInstance);
  if (Mock.MessageBroker_subscribe_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.MessageBroker_subscribe_FinalReturn;
    memcpy((void*)(&Mock.MessageBroker_subscribe_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(status_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.MessageBroker_subscribe_CallbackBool &&
      Mock.MessageBroker_subscribe_CallbackFunctionPointer != NULL)
  {
    status_t cmock_cb_ret = Mock.MessageBroker_subscribe_CallbackFunctionPointer(in_eMsgTopic, in_p32FunctionCallback, Mock.MessageBroker_subscribe_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (!cmock_call_instance->IgnoreArg_in_eMsgTopic)
  {
    UNITY_SET_DETAILS(CMockString_MessageBroker_subscribe,CMockString_in_eMsgTopic);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_in_eMsgTopic), (void*)(&in_eMsgTopic), sizeof(MessageTopics_e), cmock_line, CMockStringMismatch);
  }
  if (!cmock_call_instance->IgnoreArg_in_p32FunctionCallback)
  {
    UNITY_SET_DETAILS(CMockString_MessageBroker_subscribe,CMockString_in_p32FunctionCallback);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_in_p32FunctionCallback), (void*)(&in_p32FunctionCallback), sizeof(Module_msgCallback_t), cmock_line, CMockStringMismatch);
  }
  if (Mock.MessageBroker_subscribe_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.MessageBroker_subscribe_CallbackFunctionPointer(in_eMsgTopic, in_p32FunctionCallback, Mock.MessageBroker_subscribe_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_MessageBroker_subscribe(CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance, MessageTopics_e in_eMsgTopic, Module_msgCallback_t in_p32FunctionCallback);
void CMockExpectParameters_MessageBroker_subscribe(CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance, MessageTopics_e in_eMsgTopic, Module_msgCallback_t in_p32FunctionCallback)
{
  memcpy((void*)(&cmock_call_instance->Expected_in_eMsgTopic), (void*)(&in_eMsgTopic),
         sizeof(MessageTopics_e[sizeof(in_eMsgTopic) == sizeof(MessageTopics_e) ? 1 : -1])); /* add MessageTopics_e to :treat_as_array if this causes an error */
  cmock_call_instance->IgnoreArg_in_eMsgTopic = 0;
  memcpy((void*)(&cmock_call_instance->Expected_in_p32FunctionCallback), (void*)(&in_p32FunctionCallback),
         sizeof(Module_msgCallback_t[sizeof(in_p32FunctionCallback) == sizeof(Module_msgCallback_t) ? 1 : -1])); /* add Module_msgCallback_t to :treat_as_array if this causes an error */
  cmock_call_instance->IgnoreArg_in_p32FunctionCallback = 0;
}

void MessageBroker_subscribe_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_subscribe_CALL_INSTANCE));
  CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_subscribe_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_subscribe_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_subscribe_CallInstance, cmock_guts_index);
  Mock.MessageBroker_subscribe_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.MessageBroker_subscribe_IgnoreBool = (char)1;
}

void MessageBroker_subscribe_CMockStopIgnore(void)
{
  if(Mock.MessageBroker_subscribe_IgnoreBool)
    Mock.MessageBroker_subscribe_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_subscribe_CallInstance);
  Mock.MessageBroker_subscribe_IgnoreBool = (char)0;
}

void MessageBroker_subscribe_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, MessageTopics_e in_eMsgTopic, Module_msgCallback_t in_p32FunctionCallback, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_subscribe_CALL_INSTANCE));
  CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_subscribe_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_subscribe_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_subscribe_CallInstance, cmock_guts_index);
  Mock.MessageBroker_subscribe_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_MessageBroker_subscribe(cmock_call_instance, in_eMsgTopic, in_p32FunctionCallback);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(status_t[sizeof(cmock_to_return) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
}

void MessageBroker_subscribe_AddCallback(CMOCK_MessageBroker_subscribe_CALLBACK Callback)
{
  Mock.MessageBroker_subscribe_IgnoreBool = (char)0;
  Mock.MessageBroker_subscribe_CallbackBool = (char)1;
  Mock.MessageBroker_subscribe_CallbackFunctionPointer = Callback;
}

void MessageBroker_subscribe_Stub(CMOCK_MessageBroker_subscribe_CALLBACK Callback)
{
  Mock.MessageBroker_subscribe_IgnoreBool = (char)0;
  Mock.MessageBroker_subscribe_CallbackBool = (char)0;
  Mock.MessageBroker_subscribe_CallbackFunctionPointer = Callback;
}

void MessageBroker_subscribe_CMockIgnoreArg_in_eMsgTopic(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_subscribe_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.MessageBroker_subscribe_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_in_eMsgTopic = 1;
}

void MessageBroker_subscribe_CMockIgnoreArg_in_p32FunctionCallback(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MessageBroker_subscribe_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_subscribe_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.MessageBroker_subscribe_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_in_p32FunctionCallback = 1;
}

status_t MessageBroker_publish(MessageBroker_message_t in_tMessage)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_MessageBroker_publish);
  cmock_call_instance = (CMOCK_MessageBroker_publish_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.MessageBroker_publish_CallInstance);
  Mock.MessageBroker_publish_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_publish_CallInstance);
  if (Mock.MessageBroker_publish_IgnoreBool)
  {
    UNITY_CLR_DETAILS();
    if (cmock_call_instance == NULL)
      return Mock.MessageBroker_publish_FinalReturn;
    memcpy((void*)(&Mock.MessageBroker_publish_FinalReturn), (void*)(&cmock_call_instance->ReturnVal),
         sizeof(status_t[sizeof(cmock_call_instance->ReturnVal) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
    return cmock_call_instance->ReturnVal;
  }
  if (!Mock.MessageBroker_publish_CallbackBool &&
      Mock.MessageBroker_publish_CallbackFunctionPointer != NULL)
  {
    status_t cmock_cb_ret = Mock.MessageBroker_publish_CallbackFunctionPointer(in_tMessage, Mock.MessageBroker_publish_CallbackCalls++);
    UNITY_CLR_DETAILS();
    return cmock_cb_ret;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledEarly);
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLate);
  if (!cmock_call_instance->IgnoreArg_in_tMessage)
  {
    UNITY_SET_DETAILS(CMockString_MessageBroker_publish,CMockString_in_tMessage);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_in_tMessage), (void*)(&in_tMessage), sizeof(MessageBroker_message_t), cmock_line, CMockStringMismatch);
  }
  if (Mock.MessageBroker_publish_CallbackFunctionPointer != NULL)
  {
    cmock_call_instance->ReturnVal = Mock.MessageBroker_publish_CallbackFunctionPointer(in_tMessage, Mock.MessageBroker_publish_CallbackCalls++);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_MessageBroker_publish(CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance, MessageBroker_message_t in_tMessage);
void CMockExpectParameters_MessageBroker_publish(CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance, MessageBroker_message_t in_tMessage)
{
  memcpy((void*)(&cmock_call_instance->Expected_in_tMessage), (void*)(&in_tMessage),
         sizeof(MessageBroker_message_t[sizeof(in_tMessage) == sizeof(MessageBroker_message_t) ? 1 : -1])); /* add MessageBroker_message_t to :treat_as_array if this causes an error */
  cmock_call_instance->IgnoreArg_in_tMessage = 0;
}

void MessageBroker_publish_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_publish_CALL_INSTANCE));
  CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_publish_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_publish_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_publish_CallInstance, cmock_guts_index);
  Mock.MessageBroker_publish_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->ReturnVal = cmock_to_return;
  Mock.MessageBroker_publish_IgnoreBool = (char)1;
}

void MessageBroker_publish_CMockStopIgnore(void)
{
  if(Mock.MessageBroker_publish_IgnoreBool)
    Mock.MessageBroker_publish_CallInstance = CMock_Guts_MemNext(Mock.MessageBroker_publish_CallInstance);
  Mock.MessageBroker_publish_IgnoreBool = (char)0;
}

void MessageBroker_publish_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, MessageBroker_message_t in_tMessage, status_t cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_MessageBroker_publish_CALL_INSTANCE));
  CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_publish_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.MessageBroker_publish_CallInstance = CMock_Guts_MemChain(Mock.MessageBroker_publish_CallInstance, cmock_guts_index);
  Mock.MessageBroker_publish_IgnoreBool = (char)0;
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_MessageBroker_publish(cmock_call_instance, in_tMessage);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(status_t[sizeof(cmock_to_return) == sizeof(status_t) ? 1 : -1])); /* add status_t to :treat_as_array if this causes an error */
}

void MessageBroker_publish_AddCallback(CMOCK_MessageBroker_publish_CALLBACK Callback)
{
  Mock.MessageBroker_publish_IgnoreBool = (char)0;
  Mock.MessageBroker_publish_CallbackBool = (char)1;
  Mock.MessageBroker_publish_CallbackFunctionPointer = Callback;
}

void MessageBroker_publish_Stub(CMOCK_MessageBroker_publish_CALLBACK Callback)
{
  Mock.MessageBroker_publish_IgnoreBool = (char)0;
  Mock.MessageBroker_publish_CallbackBool = (char)0;
  Mock.MessageBroker_publish_CallbackFunctionPointer = Callback;
}

void MessageBroker_publish_CMockIgnoreArg_in_tMessage(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MessageBroker_publish_CALL_INSTANCE* cmock_call_instance = (CMOCK_MessageBroker_publish_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.MessageBroker_publish_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringIgnPreExp);
  cmock_call_instance->IgnoreArg_in_tMessage = 1;
}

