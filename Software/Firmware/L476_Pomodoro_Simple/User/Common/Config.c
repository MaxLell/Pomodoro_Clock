
#include "Config.h"

STATIC const uint8_t WORKTIME = 50;
STATIC const uint8_t BREAKTIME = 10;

uint8_t Config_getBreaktime(uint8_t *out_u8BreaktimeIntervalMin)
{
    assert_true(out_u8BreaktimeIntervalMin != NULL);
    if (out_u8BreaktimeIntervalMin == NULL)
    {
        log_error("out_u8BreaktimeIntervalMin is NULL");
        return STATUS_NULL_POINTER;
    }
    *out_u8BreaktimeIntervalMin = BREAKTIME;
    return STATUS_OK;
}

uint8_t Config_getWorktime(uint8_t *out_u8WorktimeIntervalMin)
{
    assert_true(out_u8WorktimeIntervalMin != NULL);
    if (out_u8WorktimeIntervalMin == NULL)
    {
        log_error("out_u8WorktimeIntervalMin is NULL");
        return STATUS_NULL_POINTER;
    }
    *out_u8WorktimeIntervalMin = WORKTIME;
    return STATUS_OK;
}