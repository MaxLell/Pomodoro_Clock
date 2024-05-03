#include <Arduino.h>
#include "OnBoardTest.h"
#include "Executer.h"

void setup()
{
#ifdef ONBOARDTEST
  OnBoardTest_init();
#else
  Executer_init();
#endif
}

void loop()
{
#ifdef ONBOARDTEST
  OnBoardTest_execute();
#else
  // Run the nominal procedure
  // This is still to be added in
#endif
}