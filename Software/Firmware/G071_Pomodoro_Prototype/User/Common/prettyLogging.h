#ifndef PRETTY_LOGGING_H
#define PRETTY_LOGGING_H

#include <stdio.h>
#include <string.h>

#define log_info(M, ...)                   \
        printf("[INFO]  (%s:%d): " M "\n", \
               __FILE__,                   \
               __LINE__,                   \
               ##__VA_ARGS__)

#define log_error(M, ...)                  \
        printf("[ERROR] (%s:%d): " M "\n", \
               __FILE__,                   \
               __LINE__,                   \
               ##__VA_ARGS__)

#endif /* PRETTY_LOGGING_H */
