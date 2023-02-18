/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_BUTTON_HARDWARE_H
#define _MOCK_BUTTON_HARDWARE_H

#include "unity.h"
#include "Button_Hardware.h"

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

void mock_Button_Hardware_Init(void);
void mock_Button_Hardware_Destroy(void);
void mock_Button_Hardware_Verify(void);




#define Button_Hardware_init_Ignore() Button_Hardware_init_CMockIgnore()
void Button_Hardware_init_CMockIgnore(void);
#define Button_Hardware_init_StopIgnore() Button_Hardware_init_CMockStopIgnore()
void Button_Hardware_init_CMockStopIgnore(void);
#define Button_Hardware_init_Expect() Button_Hardware_init_CMockExpect(__LINE__)
void Button_Hardware_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_Button_Hardware_init_CALLBACK)(int cmock_num_calls);
void Button_Hardware_init_AddCallback(CMOCK_Button_Hardware_init_CALLBACK Callback);
void Button_Hardware_init_Stub(CMOCK_Button_Hardware_init_CALLBACK Callback);
#define Button_Hardware_init_StubWithCallback Button_Hardware_init_Stub
#define Button_Hardware_wasPressed_IgnoreAndReturn(cmock_retval) Button_Hardware_wasPressed_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Button_Hardware_wasPressed_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return);
#define Button_Hardware_wasPressed_StopIgnore() Button_Hardware_wasPressed_CMockStopIgnore()
void Button_Hardware_wasPressed_CMockStopIgnore(void);
#define Button_Hardware_wasPressed_ExpectAndReturn(cmock_retval) Button_Hardware_wasPressed_CMockExpectAndReturn(__LINE__, cmock_retval)
void Button_Hardware_wasPressed_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, BOOL cmock_to_return);
typedef BOOL (* CMOCK_Button_Hardware_wasPressed_CALLBACK)(int cmock_num_calls);
void Button_Hardware_wasPressed_AddCallback(CMOCK_Button_Hardware_wasPressed_CALLBACK Callback);
void Button_Hardware_wasPressed_Stub(CMOCK_Button_Hardware_wasPressed_CALLBACK Callback);
#define Button_Hardware_wasPressed_StubWithCallback Button_Hardware_wasPressed_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
