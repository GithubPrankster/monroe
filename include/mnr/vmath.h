#pragma once

typedef int fixed;

#define FIXED_POINT 16 /* 16.16 */
#define SIGN_BIT 31
#define FIXED_UNIT 1 << FIXED_POINT
#define HALF_FIXED_UNIT (FIXED_UNIT >> 1)
#define QUARTER_FIXED_UNIT (FIXED_UNIT >> 2)

#define int2fix(value) ((value) << FIXED_POINT)
#define fix2int(value) ((value) >> FIXED_POINT)

int sign(int x);

// TODO: Fixed point math (mult/div)