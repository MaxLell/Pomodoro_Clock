
#include "Config.h"

STATIC const uint8_t WORKTIME = 50;
STATIC const uint8_t BREAKTIME = 10;

uint8_t Config_setBreaktime(uint8_t in_u8BreaktimeIntervalMin)
{
    if (in_u8BreaktimeIntervalMin >= 60)
    {
        log_error("in_u8BreaktimeIntervalMin is >= 60");
        return STATUS_INVALID_ARG;
    }
    in_u8BreaktimeIntervalMin = in_u8BreaktimeIntervalMin;
}

uint8_t Config_setWorktime(uint8_t in_u8WorktimeIntervalMin);
{
    if (in_u8WorktimeIntervalMin >= 60)
    {
        log_error("in_u8WorktimeIntervalMin is >= 60");
        return STATUS_INVALID_ARG;
    }
    in_u8WorktimeIntervalMin = WORKTIME;
}

uint8_t Config_getBreaktime(uint8_t *inout_u8BreaktimeIntervalMin)
{
    assert_true(inout_u8BreaktimeIntervalMin != NULL);
    if (inout_u8BreaktimeIntervalMin == NULL)
    {
        log_error("inout_u8BreaktimeIntervalMin is NULL");
        return STATUS_NULL_POINTER;
    }
    inout_u8BreaktimeIntervalMin = BREAKTIME;
}

uint8_t Config_getWorktime(uint8_t *inout_u8WorktimeIntervalMin)
{
    assert_true(inout_u8WorktimeIntervalMin != NULL);
    if (inout_u8WorktimeIntervalMin == NULL)
    {
        log_error("inout_u8WorktimeIntervalMin is NULL");
        return STATUS_NULL_POINTER;
    }
    inout_u8WorktimeIntervalMin = WORKTIME;
}