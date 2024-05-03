#ifndef ONBOARDTEST_H
#define ONBOARDTEST_H

#include "Common.h"

// #define ONBOARDTEST // Comment this line out to enable the nominal behavior

#ifdef __cplusplus
extern "C"
{
#endif

    void OnBoardTest_init(void);

    void OnBoardTest_execute(void);

#ifdef __cplusplus
}
#endif

#endif // ONBOARDTEST_H
