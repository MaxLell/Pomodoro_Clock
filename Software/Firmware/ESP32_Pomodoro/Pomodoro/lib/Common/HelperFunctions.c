
#include "stdint.h"
#include "stdlib.h"
#include "Common.h"

void HelperFunction_getPseudoRandomNumber(const u32 in_u32MinValue, const u32 in_u32MaxValue, u32 *const out_pu32RandomNumber)
{
    ASSERT_MSG(!(in_u32MaxValue <= in_u32MinValue), "values need to be different. Provided values are Min: %d, Max: %d", (int)in_u32MinValue, (int)in_u32MaxValue);
    // Null Ptr Checks
    ASSERT_MSG(NULL != out_pu32RandomNumber, "Null Pointer");

    *out_pu32RandomNumber = ((u32)rand() % (in_u32MaxValue - in_u32MinValue + 1)) + in_u32MinValue;
    return;
}