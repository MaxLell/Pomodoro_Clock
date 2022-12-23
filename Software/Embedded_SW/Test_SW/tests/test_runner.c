/*
Author: Hello (World)
test_runner.c (c) 2022
Desc: description
Created:  2022-12-23T08:54:01.460Z
Modified: !date!
*/

#include <stdio.h>
#include <stdlib.h>

#include "unity_lib/unity.h"

void setUp(void)
{
  // MANDATORY
  // set stuff up here
}

void tearDown(void)
{
  // MANDATORY
  // clean stuff up here
}

extern void test_can_cubeide_file_be_tested();

/**
 * Test Runner
 */
int main(void)
{
  UNITY_BEGIN();

  /* Tool chain test */
  RUN_TEST(test_can_cubeide_file_be_tested);

  return UNITY_END();
}