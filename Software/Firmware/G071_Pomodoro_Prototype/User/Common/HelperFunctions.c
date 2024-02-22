
#include "stdint.h"
#include "stdlib.h"
#include "Common.h"

void HelperFunction_getPseudoRandomNumber(const uint32_t in_u32MinValue, const uint32_t in_u32MaxValue, uint32_t *const out_pu32RandomNumber)
{
    ASSERT_MSG(!(in_u32MaxValue <= in_u32MinValue), "values need to be different");
    // Null Ptr Checks
    ASSERT_MSG(NULL != out_pu32RandomNumber, "Null Pointer");

    *out_pu32RandomNumber = ((uint32_t)rand() % (in_u32MaxValue - in_u32MinValue + 1)) + in_u32MinValue;
    return;
}