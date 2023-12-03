#ifndef CUSTOM_ASSERT_H
#define CUSTOM_ASSERT_H

#include "assert.h"

#ifdef TEST
#define ASSERT(x) ((void)0)
#define ASSERT_MSG(x, msg, ...)                          \
    if (!(x))                                            \
    {                                                    \
        printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", \
               __FILE__,                                 \
               __LINE__,                                 \
               #x,                                       \
               ##__VA_ARGS__);                           \
    }
// #define ASSERT_MSG(x, msg, ...) ((void)0)

#else
#define log_assert(M, ...)              \
    printf("[ASSERT] (%s:%d): " M "\n", \
           __FILE__,                    \
           __LINE__,                    \
           ##__VA_ARGS__)

#define ASSERT(x)                               \
    if (!(x))                                   \
    {                                           \
        log_assert("Assertion failed: %s", #x); \
        assert(false);                          \
    }

#define ASSERT_MSG(x, msg, ...)                          \
    if (!(x))                                            \
    {                                                    \
        printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", \
               __FILE__,                                 \
               __LINE__,                                 \
               #x,                                       \
               ##__VA_ARGS__);                           \
        assert(0);                                       \
    }

#endif //  TEST
#endif // CUSTOM_ASSERT_H
