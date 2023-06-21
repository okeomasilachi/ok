#include "main.h"

/**
 * get_bit - get the bit at a particular point
 * @n:the number to check
 * @index: position to check bit at
 *
 * Return: on success returns the bit
*/
int get_bit(unsigned long int n, unsigned int index)
{
	if (index >= sizeof(unsigned long int) * 8)
	{
		return (-1);
	}
	return ((n >> index) & 1);
}
