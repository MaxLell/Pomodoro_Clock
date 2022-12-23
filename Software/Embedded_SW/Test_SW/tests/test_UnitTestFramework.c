
#include <stdlib.h>

#include "../../Pomodoro_Clock_HW/User/UnityTest/add.h"
#include "unity_lib/unity.h"

void test_can_cubeide_file_be_tested() {
  int a = 1;
  int b = 2;
  int c = 3;
  int d = add(a, b);
  TEST_ASSERT(c == d);
}