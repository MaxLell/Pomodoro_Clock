/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_SYSTICK_H
#define _MOCK_SYSTICK_H

#include "unity.h"
#include "SysTick.h"

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

void mock_SysTick_Init(void);
void mock_SysTick_Destroy(void);
void mock_SysTick_Verify(void);




#define SysTick_init_Ignore() SysTick_init_CMockIgnore()
void SysTick_init_CMockIgnore(void);
#define SysTick_init_StopIgnore() SysTick_init_CMockStopIgnore()
void SysTick_init_CMockStopIgnore(void);
#define SysTick_init_Expect() SysTick_init_CMockExpect(__LINE__)
void SysTick_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_SysTick_init_CALLBACK)(int cmock_num_calls);
void SysTick_init_AddCallback(CMOCK_SysTick_init_CALLBACK Callback);
void SysTick_init_Stub(CMOCK_SysTick_init_CALLBACK Callback);
#define SysTick_init_StubWithCallback SysTick_init_Stub
#define SysTick_Handler_Ignore() SysTick_Handler_CMockIgnore()
void SysTick_Handler_CMockIgnore(void);
#define SysTick_Handler_StopIgnore() SysTick_Handler_CMockStopIgnore()
void SysTick_Handler_CMockStopIgnore(void);
#define SysTick_Handler_Expect() SysTick_Handler_CMockExpect(__LINE__)
void SysTick_Handler_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_SysTick_Handler_CALLBACK)(int cmock_num_calls);
void SysTick_Handler_AddCallback(CMOCK_SysTick_Handler_CALLBACK Callback);
void SysTick_Handler_Stub(CMOCK_SysTick_Handler_CALLBACK Callback);
#define SysTick_Handler_StubWithCallback SysTick_Handler_Stub
#define delay_ms_Ignore() delay_ms_CMockIgnore()
void delay_ms_CMockIgnore(void);
#define delay_ms_StopIgnore() delay_ms_CMockStopIgnore()
void delay_ms_CMockStopIgnore(void);
#define delay_ms_Expect(ms) delay_ms_CMockExpect(__LINE__, ms)
void delay_ms_CMockExpect(UNITY_LINE_TYPE cmock_line, uint32_t ms);
typedef void (* CMOCK_delay_ms_CALLBACK)(uint32_t ms, int cmock_num_calls);
void delay_ms_AddCallback(CMOCK_delay_ms_CALLBACK Callback);
void delay_ms_Stub(CMOCK_delay_ms_CALLBACK Callback);
#define delay_ms_StubWithCallback delay_ms_Stub
#define delay_ms_IgnoreArg_ms() delay_ms_CMockIgnoreArg_ms(__LINE__)
void delay_ms_CMockIgnoreArg_ms(UNITY_LINE_TYPE cmock_line);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
