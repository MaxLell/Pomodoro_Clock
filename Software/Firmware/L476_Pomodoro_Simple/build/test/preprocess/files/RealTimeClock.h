#include "User/Common/Common.h"










typedef enum

{

    E_RTC_DAY_MONDAY = 1U,

    E_RTC_DAY_TUESDAY,

    E_RTC_DAY_WEDNESDAY,

    E_RTC_DAY_THURSDAY,

    E_RTC_DAY_FRIDAY,

    E_RTC_DAY_SATURDAY,

    E_RTC_DAY_SUNDAY,

} RealTimeClock_Days_e;



typedef struct

{

    uint8_t u8Hour;

    uint8_t u8Minute;

    uint8_t u8Second;

    uint8_t u8Day;

    uint8_t u8Month;

    uint8_t u8Year;

} RealTimeClock_TimeAndDate_t;







status_t RealTimeClock_execute(void);



void RealTimeClock_init(void);
