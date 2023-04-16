/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_LIGHTCONTROL_H
#define _MOCK_LIGHTCONTROL_H

#include "unity.h"
#include "LightControl.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void mock_LightControl_Init(void);
void mock_LightControl_Destroy(void);
void mock_LightControl_Verify(void);




#define LightControl_execute_IgnoreAndReturn(cmock_retval) LightControl_execute_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void LightControl_execute_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return);
#define LightControl_execute_StopIgnore() LightControl_execute_CMockStopIgnore()
void LightControl_execute_CMockStopIgnore(void);
#define LightControl_execute_ExpectAndReturn(cmock_retval) LightControl_execute_CMockExpectAndReturn(__LINE__, cmock_retval)
void LightControl_execute_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return);
typedef status_t (* CMOCK_LightControl_execute_CALLBACK)(int cmock_num_calls);
void LightControl_execute_AddCallback(CMOCK_LightControl_execute_CALLBACK Callback);
void LightControl_execute_Stub(CMOCK_LightControl_execute_CALLBACK Callback);
#define LightControl_execute_StubWithCallback LightControl_execute_Stub
#define LightControl_init_Ignore() LightControl_init_CMockIgnore()
void LightControl_init_CMockIgnore(void);
#define LightControl_init_StopIgnore() LightControl_init_CMockStopIgnore()
void LightControl_init_CMockStopIgnore(void);
#define LightControl_init_Expect() LightControl_init_CMockExpect(__LINE__)
void LightControl_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_LightControl_init_CALLBACK)(int cmock_num_calls);
void LightControl_init_AddCallback(CMOCK_LightControl_init_CALLBACK Callback);
void LightControl_init_Stub(CMOCK_LightControl_init_CALLBACK Callback);
#define LightControl_init_StubWithCallback LightControl_init_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
