#ifndef ONBOARDTEST_H
#define ONBOARDTEST_H

#include "Common.h"

/************************************************************
 * Public Defines
 ************************************************************/

#ifndef NO_DEBUG
#define RUN_ON_BOARD_TEST
#endif

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
