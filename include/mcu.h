#ifndef MCU_H_
#define MCU_H_

#define F_CPU 3333333L

#define _NOP() do { __asm__ __volatile__ ("nop"); } while (0)

#endif /* MCU_H_ */