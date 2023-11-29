#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>
//--------------------------------------------
// Add a helpful status type and codes
//--------------------------------------------
typedef uint8_t status_t;

#define STATUS_OK (0)

#define STATUS_UNKNOWN_CMD (1)
#define STATUS_MISSING_ARG (2)
#define STATUS_EXTRA_ARG (3)
#define STATUS_INVALID_ARG (4)
#define STATUS_TOO_LOW (5)
#define STATUS_TOO_HIGH (6)

#define STATUS_BAD_MSG (7)

#define STATUS_NOT_ARMED (10)
#define STATUS_NONE_YET (11)
#define STATUS_CAPTURING (12)
#define STATUS_OVERFLOW (13)
#define STATUS_MISSING_DATA (14)
#define STATUS_ALREADY_TRIGGERED (15)
#define STATUS_ALREADY_ARMED (16)
#define STATUS_ALREADY_COMPLETE (17)

#define STATUS_INVALID_PARAM (20)
#define STATUS_TOO_MANY_PARAMS (21)

#define STATUS_NOT_INITIALIZED (30)

#define STATUS_NULL_POINTER (31)

#define STATUS_UNKNOWN_ERR (255)

#endif // STATUS_H