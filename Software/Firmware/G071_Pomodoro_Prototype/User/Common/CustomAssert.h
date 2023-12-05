#ifndef CUSTOM_ASSERT_H
#define CUSTOM_ASSERT_H

#ifdef TEST
#define ASSERT(x) ((void)0)
#define ASSERT_MSG(x, msg, ...)                                              \
  if (!(x)) {                                                                \
    printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", __FILE__, __LINE__, #x, \
           ##__VA_ARGS__);                                                   \
  }

#else
#define log_assert(M, ...) \
  printf("[ASSERT] (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define ASSERT(x)                           \
  if (!(x)) {                               \
    log_assert("Assertion failed: %s", #x); \
    while (1)                               \
      ;                                     \
  }

#define ASSERT_MSG(x, msg, ...)                                              \
  if (!(x)) {                                                                \
    printf("[ASSERT FAIL] (%s:%d): (%s): " msg "\n", __FILE__, __LINE__, #x, \
           ##__VA_ARGS__);                                                   \
    while (1)                                                                \
      ;                                                                      \
  }

#endif  //  TEST
#endif  // CUSTOM_ASSERT_H
