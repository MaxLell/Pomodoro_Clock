#include "Button_Hardware.h"

#include "main.h"

STATIC BOOL bButtonWasPressed;

void Button_Hardware_init() { bButtonWasPressed = FALSE; }

BOOL Button_Hardware_wasPressed() {
  BOOL tmp;
  tmp = bButtonWasPressed;
  bButtonWasPressed = FALSE;
  return tmp;
}

void Button_Hardware_Interrupt() { bButtonWasPressed = TRUE; }
