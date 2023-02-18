/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_EXECUTER_H
#define _MOCK_EXECUTER_H

#include "unity.h"
#include "Executer.h"

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

void mock_Executer_Init(void);
void mock_Executer_Destroy(void);
void mock_Executer_Verify(void);




#define Executer_init_Ignore() Executer_init_CMockIgnore()
void Executer_init_CMockIgnore(void);
#define Executer_init_StopIgnore() Executer_init_CMockStopIgnore()
void Executer_init_CMockStopIgnore(void);
#define Executer_init_Expect() Executer_init_CMockExpect(__LINE__)
void Executer_init_CMockExpect(UNITY_LINE_TYPE cmock_line);
typedef void (* CMOCK_Executer_init_CALLBACK)(int cmock_num_calls);
void Executer_init_AddCallback(CMOCK_Executer_init_CALLBACK Callback);
void Executer_init_Stub(CMOCK_Executer_init_CALLBACK Callback);
#define Executer_init_StubWithCallback Executer_init_Stub
#define Executer_exec_IgnoreAndReturn(cmock_retval) Executer_exec_CMockIgnoreAndReturn(__LINE__, cmock_retval)
void Executer_exec_CMockIgnoreAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return);
#define Executer_exec_StopIgnore() Executer_exec_CMockStopIgnore()
void Executer_exec_CMockStopIgnore(void);
#define Executer_exec_ExpectAndReturn(cmock_retval) Executer_exec_CMockExpectAndReturn(__LINE__, cmock_retval)
void Executer_exec_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, status_t cmock_to_return);
typedef status_t (* CMOCK_Executer_exec_CALLBACK)(int cmock_num_calls);
void Executer_exec_AddCallback(CMOCK_Executer_exec_CALLBACK Callback);
void Executer_exec_Stub(CMOCK_Executer_exec_CALLBACK Callback);
#define Executer_exec_StubWithCallback Executer_exec_Stub

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
