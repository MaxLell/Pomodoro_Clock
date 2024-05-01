#ifndef STATUS_H
#define STATUS_H

/**
 * These Status codes are inspired by HTTP status codes.
 * https://developer.mozilla.org/en-US/docs/Web/HTTP/Status#information_responses
 */

typedef enum
{
  STATUS_IN_PROGRESS = 102,
  STATUS_OK = 200,
  STATUS_ERROR = 400,
} status_e;

#endif // STATUS_H
