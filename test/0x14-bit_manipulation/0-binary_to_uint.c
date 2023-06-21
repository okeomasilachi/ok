#include "main.h"

/**
 * binary_to_uint - converts binary to unsigned int
 * @b: binary integer to be converted
 *
 * Return: returns the unsigned int convertion of the bin num
 */

unsigned int binary_to_uint(const char *b)
{
	unsigned int ans = 0;
	int i;

	if (b == NULL)
		return (0);

	for (i = 0; b[i] != '\0'; i++)
	{
		if (b[i] == '0')
		{
			ans = (ans << 1) | 0;
		}
		else if (b[i] == '1')
		{
			ans = (ans << 1) | 1;
		}
		else
		{
			return (0);
		}
	}
	return (ans);
}
