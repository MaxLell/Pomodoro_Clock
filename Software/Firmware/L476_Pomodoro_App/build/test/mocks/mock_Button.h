/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_BUTTON_H
#define _MOCK_BUTTON_H

#include "unity.h"
#include "Button.h"

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

void mock_Button_Init(void);
void mock_Button_Destroy(void);
void mock_Button_Verify(void);




#define Button_init_Ignore() Button_init_CMockIgnore()
void Button_init_CMockIgnore(void);
#define Button_init_StopIgnore() Button_init_CMockStopIgnore()
void Button_init_CMockStopIgnore(void);
#define Button_init_Expect() Button_init_CMockExpect(__LINE__)
void Button_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_Button_init_CALLBACK)(int cmock_num_calls);
void Button_init_AddCallback(CMOCK_Button_init_CALLBACK Callback);
void Button_init_Stub(CMOCK_Button_init_CALLBACK Callback);
#define Button_init_StubWithCallback Button_init_Stub
#define Button_getState_IgnoreAndReturn(cmock_retval) Button_getState_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Button_getState_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, Button_State cmock_to_return);
#define Button_getState_StopIgnore() Button_getState_CMockStopIgnore()
void Button_getState_CMockStopIgnore(void);
#define Button_getState_ExpectAndReturn(cmock_retval) Button_getState_CMockExpectAndReturn(__LINE__, cmock_retval)
void Button_getState_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, Button_State cmock_to_return);
typedef Button_State (* CMOCK_Button_getState_CALLBACK)(int cmock_num_calls);
void Button_getState_AddCallback(CMOCK_Button_getState_CALLBACK Callback);
void Button_getState_Stub(CMOCK_Button_getState_CALLBACK Callback);
#define Button_getState_StubWithCallback Button_getState_Stub
#define Button_wasPressedSinceLastRead_IgnoreAndReturn(cmock_retval) Button_wasPressedSinceLastRead_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Button_wasPressedSinceLastRead_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return);
#define Button_wasPressedSinceLastRead_StopIgnore() Button_wasPressedSinceLastRead_CMockStopIgnore()
void Button_wasPressedSinceLastRead_CMockStopIgnore(void);
#define Button_wasPressedSinceLastRead_ExpectAndReturn(cmock_retval) Button_wasPressedSinceLastRead_CMockExpectAndReturn(__LINE__, cmock_retval)
void Button_wasPressedSinceLastRead_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return);
typedef BOOL (* CMOCK_Button_wasPressedSinceLastRead_CALLBACK)(int cmock_num_calls);
void Button_wasPressedSinceLastRead_AddCallback(CMOCK_Button_wasPressedSinceLastRead_CALLBACK Callback);
void Button_wasPressedSinceLastRead_Stub(CMOCK_Button_wasPressedSinceLastRead_CALLBACK Callback);
#define Button_wasPressedSinceLastRead_StubWithCallback Button_wasPressedSinceLastRead_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif