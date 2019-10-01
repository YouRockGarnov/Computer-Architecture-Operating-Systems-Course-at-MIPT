#include "stdio.h"
#include <stdint.h>

uint16_t satsum (const uint16_t num1, const uint16_t num2) {
	uint16_t sm = num1 + num2;

	if (sm < num1 && sm < num2)
		return ~0;
	else
		return sm;
}
