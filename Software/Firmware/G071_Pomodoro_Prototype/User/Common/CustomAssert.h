#ifndef CUSTOM_ASSERT_H
#define CUSTOM_ASSERT_H

// #define NO_DEBUG

#ifndef NO_DEBUG

#ifndef TEST
#include "BlinkyLed.h"
#include "Delay.h"
#endif //  TEST

#define log_assert(M, ...) printf("[ASSERT] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#ifdef TEST

#define ASSERT(x)                                                                                                      \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
        log_assert("Assertion failed: %s", #x);                                                                        \
    }

#define ASSERT_MSG(x, msg, ...)                                                                                        \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
        printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", __FILE__, __LINE__, #x, ##__VA_ARGS__);                       \
    }

#else

#define ASSERT(x)                                                                                                      \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
        log_assert("Assertion failed: %s", #x);                                                                        \
        while (1)                                                                                                      \
            ;                                                                                                          \
    }

#define ASSERT_MSG(x, msg, ...)                                                                                        \
    if (!(x))                                                                                                          \
    {                                                                                                                  \
        printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", __FILE__, __LINE__, #x, ##__VA_ARGS__);                       \
        while (1)                                                                                                      \
        {                                                                                                              \
            BlinkyLed_toggle();                                                                                        \
            Delay_ms(100);                                                                                             \
        }                                                                                                              \
    }

#endif // TEST

#else

#define ASSERT(x)
#define ASSERT_MSG(x, msg, ...)
#define log_assert(M, ...)

#endif // DEBUG

/**
 * Taken from
 * https://stackoverflow.com/questions/4851075/universally-compiler-independent-way-of-implementing-an-unused-macro-in-c-c
 */
#ifndef unused

#define unused(X) ((void)(0)) // To avoid compiler warnings

#endif // UNUSED

#endif // CUSTOM_ASSERT_H
