/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_BLINKYLED_H
#define _MOCK_BLINKYLED_H

#include "unity.h"
#include "BlinkyLed.h"

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

void mock_BlinkyLed_Init(void);
void mock_BlinkyLed_Destroy(void);
void mock_BlinkyLed_Verify(void);




#define BlinkyLed_toggle_Ignore() BlinkyLed_toggle_CMockIgnore()
void BlinkyLed_toggle_CMockIgnore(void);
#define BlinkyLed_toggle_StopIgnore() BlinkyLed_toggle_CMockStopIgnore()
void BlinkyLed_toggle_CMockStopIgnore(void);
#define BlinkyLed_toggle_Expect() BlinkyLed_toggle_CMockExpect(__LINE__)
void BlinkyLed_toggle_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_BlinkyLed_toggle_CALLBACK)(int cmock_num_calls);
void BlinkyLed_toggle_AddCallback(CMOCK_BlinkyLed_toggle_CALLBACK Callback);
void BlinkyLed_toggle_Stub(CMOCK_BlinkyLed_toggle_CALLBACK Callback);
#define BlinkyLed_toggle_StubWithCallback BlinkyLed_toggle_Stub
#define BlinkyLed_enable_Ignore() BlinkyLed_enable_CMockIgnore()
void BlinkyLed_enable_CMockIgnore(void);
#define BlinkyLed_enable_StopIgnore() BlinkyLed_enable_CMockStopIgnore()
void BlinkyLed_enable_CMockStopIgnore(void);
#define BlinkyLed_enable_Expect() BlinkyLed_enable_CMockExpect(__LINE__)
void BlinkyLed_enable_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_BlinkyLed_enable_CALLBACK)(int cmock_num_calls);
void BlinkyLed_enable_AddCallback(CMOCK_BlinkyLed_enable_CALLBACK Callback);
void BlinkyLed_enable_Stub(CMOCK_BlinkyLed_enable_CALLBACK Callback);
#define BlinkyLed_enable_StubWithCallback BlinkyLed_enable_Stub
#define BlinkyLed_disable_Ignore() BlinkyLed_disable_CMockIgnore()
void BlinkyLed_disable_CMockIgnore(void);
#define BlinkyLed_disable_StopIgnore() BlinkyLed_disable_CMockStopIgnore()
void BlinkyLed_disable_CMockStopIgnore(void);
#define BlinkyLed_disable_Expect() BlinkyLed_disable_CMockExpect(__LINE__)
void BlinkyLed_disable_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_BlinkyLed_disable_CALLBACK)(int cmock_num_calls);
void BlinkyLed_disable_AddCallback(CMOCK_BlinkyLed_disable_CALLBACK Callback);
void BlinkyLed_disable_Stub(CMOCK_BlinkyLed_disable_CALLBACK Callback);
#define BlinkyLed_disable_StubWithCallback BlinkyLed_disable_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
