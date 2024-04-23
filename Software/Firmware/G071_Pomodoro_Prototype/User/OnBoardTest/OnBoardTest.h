#ifndef ONBOARDTEST_H
#define ONBOARDTEST_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/

#define RUN_ON_BOARD_TEST

/************************************************************
 * Public Datastructures
 ************************************************************/

/************************************************************
 * Public functions
 ************************************************************/
BOOL OnBoardTest_isRunning(void);

void OnBoardTest_init(void);

void OnBoardTest_execute(void);

#endif // ONBOARDTEST_H
