#include "include/eeprom.h"

#include <avr/io.h>

/*
 * Read seed from EEPROM, increment, return and store it back
 */
uint16_t eeprom_get_next_seed()
{
	uint16_t seed = (SEED_REG_HIGH << 8) | SEED_REG_LOW;
	
	seed++;
	
	SEED_REG_HIGH = seed >> 8;
	SEED_REG_LOW = seed & 0xFF;
	
	NVMCTRL.ADDR = EEPROM_ADDR_LOW;
	
	CPU_CCP = CCP_SPM_gc;
	NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEERASEWRITE_gc;
	
	NVMCTRL.ADDR = EEPROM_ADDR_HIGH;
	
	CPU_CCP = CCP_SPM_gc;
	NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEERASEWRITE_gc;
	
	return seed;
}