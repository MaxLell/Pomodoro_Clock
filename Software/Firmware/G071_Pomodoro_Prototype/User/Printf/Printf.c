/*
 * Debug.c
 *
 *  Created on: Dec 7, 2021
 *      Author: maxlell
 */

#include "Printf.h"

static UART_HandleTypeDef *uart;

#ifdef SERIAL_COM

int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(uart, (uint8_t *)ptr, len, HAL_MAX_DELAY);
  return len;
}

void Printf_SetUartPort(UART_HandleTypeDef *huart)
{
  uart = huart;
}

#endif

#ifdef SWV_TRACE
/*
 * Procedure on how to enable SWV Debugging
 * - Launch Debug Configuration
 * - Go to Tab „Debugger“
 * - Set Debug Probe to „ST-LINK (ST-LINK GDB Server)
 * - Serial Wire Viewer (SWV)
 *   - Set the Enable Flag
 *   - Set the Core Clock to the Main Core Clock Setting (Clocks Tab in the STM32Cube-IOC File)
 *   - Confirm Settings with „Apply“ and „Debug“ Buttons
 *
 *   - Go to Window -> Show View -> SWV -> SWV Data Console (The Tab should now appear in the Bottum
 *     Part of the IDE - next to the Console Tab)
 *   - In this Tab (SWV ITM Data Console) click on „Configure Trace“ (the wrench with the screwdriver)
 *   - Under ITM Stimulus Ports enable port 0
 *   - Click Ok
 *
 *   - In order to display the printf command click on „Record“ (The Red button)
 *   - Press „Resume“ on the top and let the code run
 */
int _write(int file, char *ptr, int len)
{
  /* Implement your write code here, this is used by puts and printf for example */
  int i = 0;
  for (i = 0; i < len; i++)
    ITM_SendChar((*ptr++));
  return len;
}
#endif
