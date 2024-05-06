#include <Arduino.h>
#include "OnBoardTest.h"
#include "Executer.h"

void setup()
{
#ifdef ONBOARDTEST
  OnBoardTest_init();
#else
  Executer_init();
  vTaskDelete(NULL);
#endif
}

void loop()
{
#ifdef ONBOARDTEST
  OnBoardTest_execute();
#else
  Executer_execute();
#endif
}