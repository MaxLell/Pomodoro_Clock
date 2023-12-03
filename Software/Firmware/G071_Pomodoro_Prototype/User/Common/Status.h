#ifndef STATUS_H
#define STATUS_H

typedef enum
{
    STATUS_AVAILABLE = 1,
    STATUS_OK = 0,
    STATUS_ERROR = -1,
    STATUS_UNAVAILABLE = -2,
    STATUS_UNKNOWN_ERROR = -3,
    STATUS_NULL_POINTER = -4
} status_t;

#endif // STATUS_H
