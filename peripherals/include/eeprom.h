#include <avr/io.h>

#ifndef EEPROM_H_
#define EEPROM_H_

uint16_t eeprom_get_next_seed();

#define EEPROM_ADDR_LOW		0x1400
#define EEPROM_ADDR_HIGH	0x1401

#define SEED_REG_LOW	_SFR_MEM8(EEPROM_ADDR_LOW)
#define SEED_REG_HIGH	_SFR_MEM8(EEPROM_ADDR_HIGH)

#endif /* EEPROM_H_ */