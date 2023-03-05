#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SIZE_OF(a) (sizeof(a) / sizeof(a[0]))

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...)                     \
        printf(" DEBUG  (%s:%d) " M "\n", \
               __FILE__,                  \
               __LINE__,                  \
               ##__VA_ARGS__)
#endif

#define clean_errno() \
        (errno == 0 ? "None" : strerror(errno))

#define log_error(M, ...)                         \
        printf(                                   \
            "[ERROR] (%s:%d: errno: %s) " M "\n", \
            __FILE__,                             \
            __LINE__,                             \
            clean_errno(),                        \
            ##__VA_ARGS__)

#define log_warning(M, ...)                       \
        printf(                                   \
            "[WARN]  (%s:%d: errno: %s) " M "\n", \
            __FILE__,                             \
            __LINE__,                             \
            clean_errno(),                        \
            ##__VA_ARGS__)

#define log_info(M, ...)                  \
        printf("[INFO]  (%s:%d) " M "\n", \
               __FILE__,                  \
               __LINE__,                  \
               ##__VA_ARGS__)

#define check(A, M, ...)                     \
        if (!(A))                            \
        {                                    \
                log_error(M, ##__VA_ARGS__); \
                errno = 0;                   \
                goto error;                  \
        }

#define sentinel(M, ...)                     \
        {                                    \
                log_error(M, ##__VA_ARGS__); \
                errno = 0;                   \
                goto error;                  \
        }

#define check_memory(A) \
        check((A), "Out of memory.")

#define check_debug(A, M, ...)           \
        if (!(A))                        \
        {                                \
                debug(M, ##__VA_ARGS__); \
                errno = 0;               \
                goto error;              \
        }

#endif
