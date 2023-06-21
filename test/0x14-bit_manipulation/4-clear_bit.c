#include "main.h"

/**
 * clear_bit - clears a bit at a particular index
 * @n: value to clear
 * @index: position (index) to clear
 *
 * Return: on success 1 else -1
*/
int clear_bit(unsigned long int *n, unsigned int index)
{
	if (index >= sizeof(unsigned long int) * 8)
	{
		return (-1);
	}
	*n &= ~(1UL << index);
	return (1);
}
