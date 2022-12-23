/*
 * Filename: /Users/maxlell/Documents/GitHub/Pomodoro_Clock/Software/Embedded_SW/Test_SW/tests/test_UnitTestFramework.c
 * Path: /Users/maxlell/Documents/GitHub/Pomodoro_Clock/Software/Embedded_SW/Test_SW/tests
 * Created Date: Friday, December 23rd 2022, 9:50:25 am
 * Author: Max Lell
 *
 * Copyright (c) 2022 Your Company
 */

#include <stdlib.h>

#include "../../Pomodoro_Clock_HW/User/Common/dbg.h"
/*
Author: Hello (World)
test_UnitTestFramework.c (c) 2022
Desc: description
Created:  2022-12-23T08:55:08.162Z
Modified: !date!
*/

#include "../../Pomodoro_Clock_HW/User/UnityTest/add.h"
#include "unity_lib/unity.h"

void test_can_cubeide_file_be_tested()
{
  int a = 1;
  int b = 2;
  int c = 3;

  /* Run the dummy function that is in the CubeIDE Project */
  int d = add(a, b);

  /* check whether the debug makro has been loaded properly */
  log_info("Assert: %d", (c == d));

  /* Check whether the Unity Command can be executed properly */
  TEST_ASSERT(c == d);
}