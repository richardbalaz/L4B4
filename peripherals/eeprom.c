#include "include/eeprom.h"

#include <avr/io.h>

/*
 * Read seed from EEPROM, increment, return and store it back
 */
uint16_t eeprom_get_next_seed()
{
	uint16_t seed = (eeprom_read(EEPROM_ADDR_HIGH) << 8) | eeprom_read(EEPROM_ADDR_LOW);
	
	seed++;
	
	eeprom_write(EEPROM_ADDR_HIGH, seed >> 8);
	eeprom_write(EEPROM_ADDR_LOW, seed & 0xFF);
	
	return seed;
}

/*
 * Write byte to specific address in EEPROM
 */
void eeprom_write(uint16_t addr, uint8_t data)
{
	uint16_t *addr_ptr = (uint16_t *) addr;
	
	*addr_ptr = data;
	NVMCTRL.ADDR = addr;
	
	CPU_CCP = CCP_SPM_gc;
	NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEERASEWRITE_gc;	
}

/*
 * Read byte from specific address in EEPROM
 */
uint8_t eeprom_read(uint16_t addr)
{
	uint16_t *addr_ptr = (uint16_t *) addr;
	
	return *addr_ptr;
}