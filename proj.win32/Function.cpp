
#include "stdio.h"
#include "stdlib.h"

//Random(int min, int max)
inline int Random(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1) * (max - min) + min;
}