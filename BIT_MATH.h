#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(reg, bit) (reg = reg | (1 << bit))

#define CLR_BIT(reg, bit) (reg = reg & ~(1 << bit))

#define TOG_BIT(reg, bit) (reg = reg ^ (1 << bit))

#define GET_BIT(reg, bit) (((reg) >> (bit)) & 1)

#endif
