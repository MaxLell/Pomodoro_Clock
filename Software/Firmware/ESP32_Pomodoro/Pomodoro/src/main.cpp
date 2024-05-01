#include <Arduino.h>
#include "OnBoardTest.h"

void setup()
{
#ifdef DBG
  OnBoardTest_init();
#else
  // Run the nominal procedure
  // This is still to be added in
#endif
}

void loop()
{
#ifdef DBG
  OnBoardTest_execute();
#else
  // Run the nominal procedure
  // This is still to be added in
#endif
}