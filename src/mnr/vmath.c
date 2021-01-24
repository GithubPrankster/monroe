#include "mnr/vmath.h"

int sign(int x)
{
	return (x >> SIGN_BIT) | ((unsigned)-x >> SIGN_BIT);
}