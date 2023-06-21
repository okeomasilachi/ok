#include "main.h"

/**
 * flip_bits - number of bit to flip to get from one number to another
 * @n: value to flip from
 * @m: value to change to
 *
 * Return: the number of bits to flip
*/

unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int x = n ^ m;
	unsigned int i = 0;

	while (x != 0)
	{
		i += x & 1;
		x >>= 1;
	}
	return (i);
}
