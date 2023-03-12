#ifndef DBGMACROS_H
#define DBGMACROS_H

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef TEST
#define TEST_RUNNING 1
#else
#define TEST_RUNNING 0
#endif

#define SIZE_OF(a) (sizeof(a) / sizeof(a[0]))

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) \
  printf(" DEBUG  (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_error(M, ...)                                          \
  printf("[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \
         clean_errno(), ##__VA_ARGS__)

#define log_warning(M, ...)                                        \
  printf("[WARN]  (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, \
         clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) \
  printf("[INFO]  (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...)         \
  if (!(A)) {                    \
    log_error(M, ##__VA_ARGS__); \
    errno = 0;                   \
    goto error;                  \
  }

#define sentinel(M, ...)         \
  {                              \
    log_error(M, ##__VA_ARGS__); \
    errno = 0;                   \
    goto error;                  \
  }

#define check_memory(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) \
  if (!(A)) {                  \
    debug(M, ##__VA_ARGS__);   \
    errno = 0;                 \
    goto error;                \
  }

#define assert_true(expression)                                      \
  if (expression) {                                                  \
    (void)0U;                                                        \
  } else {                                                           \
    if ((TEST_RUNNING == 1)) {                                       \
      printf("[ASSERT FAILURE] (%s:%d)", (char*)__FILE__, __LINE__); \
    } else {                                                         \
      printf("[ASSERT FAILURE] (%s:%d)", (char*)__FILE__, __LINE__); \
      while (1)                                                      \
        ;                                                            \
    }                                                                \
  }

#endif  // DBGMACROS_H
