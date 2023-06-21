#include "main.h"
/**
 * print_binary - print the binary representation of a number
 * @n: number to convert
 *
 * Return: void
 */

void print_binary(unsigned long int n)
{
	unsigned long int mask = 1UL << (sizeof(unsigned long int) * 8 - 1), i;
	int first_one = -1;

	for (i = 0; i < sizeof(unsigned long int) * 8; i++)
	{
		if ((n & mask) != 0)
		{
			first_one = i;
			break;
		}
		mask >>= 1;
	}

	if (first_one == -1)
	{
		_putchar('0');
	}
	else
	{
		for (i = first_one; i < sizeof(unsigned long int) * 8; i++)
		{
			_putchar((n & mask) ? '1' : '0');
			mask >>= 1;
		}
	}
}
