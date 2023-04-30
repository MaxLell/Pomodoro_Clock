/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCK_RGBLED_HARDWARE_H
#define _MOCK_RGBLED_HARDWARE_H

#include "unity.h"
#include "RgbLed_Hardware.h"

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

void mock_RgbLed_Hardware_Init(void);
void mock_RgbLed_Hardware_Destroy(void);
void mock_RgbLed_Hardware_Verify(void);




#define RgbLed_SetLeds_Ignore() RgbLed_SetLeds_CMockIgnore()
void RgbLed_SetLeds_CMockIgnore(void);
#define RgbLed_SetLeds_StopIgnore() RgbLed_SetLeds_CMockStopIgnore()
void RgbLed_SetLeds_CMockStopIgnore(void);
#define RgbLed_SetLeds_Expect(au16PwmData, u16PwmDataSize) RgbLed_SetLeds_CMockExpect(__LINE__, au16PwmData, u16PwmDataSize)
void RgbLed_SetLeds_CMockExpect(UNITY_LINE_TYPE cmock_line, uint16_t* au16PwmData, uint16_t u16PwmDataSize);
typedef void (* CMOCK_RgbLed_SetLeds_CALLBACK)(uint16_t* au16PwmData, uint16_t u16PwmDataSize, int cmock_num_calls);
void RgbLed_SetLeds_AddCallback(CMOCK_RgbLed_SetLeds_CALLBACK Callback);
void RgbLed_SetLeds_Stub(CMOCK_RgbLed_SetLeds_CALLBACK Callback);
#define RgbLed_SetLeds_StubWithCallback RgbLed_SetLeds_Stub
#define RgbLed_SetLeds_ReturnThruPtr_au16PwmData(au16PwmData) RgbLed_SetLeds_CMockReturnMemThruPtr_au16PwmData(__LINE__, au16PwmData, sizeof(uint16_t))
#define RgbLed_SetLeds_ReturnArrayThruPtr_au16PwmData(au16PwmData, cmock_len) RgbLed_SetLeds_CMockReturnMemThruPtr_au16PwmData(__LINE__, au16PwmData, cmock_len * sizeof(*au16PwmData))
#define RgbLed_SetLeds_ReturnMemThruPtr_au16PwmData(au16PwmData, cmock_size) RgbLed_SetLeds_CMockReturnMemThruPtr_au16PwmData(__LINE__, au16PwmData, cmock_size)
void RgbLed_SetLeds_CMockReturnMemThruPtr_au16PwmData(UNITY_LINE_TYPE cmock_line, uint16_t* au16PwmData, size_t cmock_size);
#define RgbLed_SetLeds_IgnoreArg_au16PwmData() RgbLed_SetLeds_CMockIgnoreArg_au16PwmData(__LINE__)
void RgbLed_SetLeds_CMockIgnoreArg_au16PwmData(UNITY_LINE_TYPE cmock_line);
#define RgbLed_SetLeds_IgnoreArg_u16PwmDataSize() RgbLed_SetLeds_CMockIgnoreArg_u16PwmDataSize(__LINE__)
void RgbLed_SetLeds_CMockIgnoreArg_u16PwmDataSize(UNITY_LINE_TYPE cmock_line);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif
