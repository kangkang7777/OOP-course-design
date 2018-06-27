#ifndef _Function_CPP_
#define _Function_CPP_


#include "stdio.h"
#include "stdlib.h"
#include "Function.h"
//Random(int min, int max)
int Random(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1) * (max - min) + min;
}
#endif