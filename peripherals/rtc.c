#include "include/rtc.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void (*rtc_overflow_handler)();

/*
 * Initialize RTC - Real Time Counter
 */
void rtc_init(void (*rtc_event_overflow_handler)())
{
	/* Set RTC speed to 1KHz */
	RTC.CLKSEL = RTC_CLKSEL_INT1K_gc; 
	
	/* Set RTC prescaler to /1 (no division) */
	rtc_synchronise(RTC_CTRLABUSY_bm);
	RTC.CTRLA = RTC_PRESCALER_DIV1_gc;
	rtc_synchronise(RTC_CTRLABUSY_bm);

	rtc_overflow_handler = rtc_event_overflow_handler;
}

/*
 * Enable RTC and starting counting
 */
void rtc_enable()
{
	/* Reset counter */
	rtc_synchronise(RTC_CNTBUSY_bm);
	RTC.CNT = 0;
	rtc_synchronise(RTC_CNTBUSY_bm);
	
	/* Enable overflow interrupt */
	RTC.INTCTRL = RTC_OVF_bm;
	
	/* Enable counter */
	RTC.CTRLA |= RTC_RTCEN_bm;
}

/*
 * Disable RTC and stop counting
 */
void rtc_disable()
{
	/* Disable overflow interrupt */
	RTC.INTCTRL &= ~RTC_OVF_bm;
	
	/* Disable counter */
	RTC.CTRLA &= ~RTC_RTCEN_bm;
}

/*
 * Set overflow timeout in milliseconds
 */
void rtc_set_timeout(int millis)
{
	rtc_synchronise(RTC_PERBUSY_bm);
	RTC.PER = millis;
	rtc_synchronise(RTC_PERBUSY_bm);
}

/*
 * Wait for register synchronization of bit masked register from status
 */
void rtc_synchronise(int bitmask)
{
	while (RTC.STATUS & bitmask)
		continue;
}

/*
 * Interrupt service routine for RTC counter
 */
ISR(RTC_CNT_vect)
{
	/* Call handler */
	(*rtc_overflow_handler)();
	
	/* Clear interrupt flag, so the next one can occur */
	RTC.INTFLAGS = 0xff;
}