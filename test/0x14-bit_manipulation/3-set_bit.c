#include "main.h"

/**
 * set_bit - sets value of a bit to 1
 * @n: value to set
 * @index:index to set
 *
 * Return: returns 1 on success else -1
*/

int set_bit(unsigned long int *n, unsigned int index)
{
	if (index >= sizeof(unsigned long int) * 8)
	{
		return (-1);
	}
	*n |= (1UL << index);

	return (1);
}
