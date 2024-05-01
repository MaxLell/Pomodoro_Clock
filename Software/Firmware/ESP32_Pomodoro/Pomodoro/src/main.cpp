#include <Arduino.h>
#include "OnBoardTest.h"
#include "InputSampling.h"

void setup()
{
#ifdef DBG
  OnBoardTest_init();
#else
  InputSampling_taskCreate();
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