#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include <stdint.h>

//--------------------------------------------
// application version
//--------------------------------------------
#define VERSION_MAJOR (0)
#define VERSION_MINOR (1)

//--------------------------------------------
// useful test overrides
//--------------------------------------------
#ifdef TEST
#define FOREVER (0)
#define STATIC
#define INLINE
#else
#define FOREVER (1)
#define STATIC static
#define INLINE inline
#endif

//--------------------------------------------
// Add simple types that aren't standard C
//--------------------------------------------
typedef unsigned char BOOL;
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL 0
#endif

//--------------------------------------------
// Add a helpful status type and codes
//--------------------------------------------
typedef int STATUS_T;
typedef uint8_t PARAM_ID_T;

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

#define STATUS_UART_BAD_PORT (40)

#define STATUS_UNKNOWN_ERR (255)

#endif /* TEST_SUPPORT_H */