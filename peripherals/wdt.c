#include "include/wdt.h"

#include <avr/io.h>

/*
 * Reset the MCU after 8ms
 */
void wdt_mcu_reset()
{
	/* Request the access for protected I/O */
	CPU_CCP = CCP_IOREG_gc;
	
	/* Set timer to 8ms */
	WDT.CTRLA = WDT_PERIOD_8CLK_gc;
	
	/* Wait for reset */
	while(1)
		continue;
}

/*
 * Set watchdog timer to 8 seconds
 */
void wdt_on()
{
	/* Request the access for protected I/O */
	CPU_CCP = CCP_IOREG_gc;
	/* Set timer to 8s */
	WDT.CTRLA = WDT_PERIOD_8KCLK_gc;	
}

/*
 * Turn the ticking watchdog timer off
 */
void wdt_off()
{
	/* Request the access for protected I/O */
	CPU_CCP = CCP_IOREG_gc;
	/* Disable WDT */
	WDT.CTRLA = WDT_PERIOD_OFF_gc;	
}