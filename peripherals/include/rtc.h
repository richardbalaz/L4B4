#include <avr/io.h>

#ifndef RTC_H_
#define RTC_H_

void rtc_init(void (*rtc_event_overflow_handler)());
void rtc_set_timeout(int millis);
void rtc_enable();
void rtc_disable();

void rtc_synchronise(int bitmask);

#endif /* RTC_H_ */