#include "main.h"

/**
 * get_endianness - gets the endianness of a system
 *
 * Return: 1 for little and 0 for big
*/
int get_endianness(void)
{
	int num = 1;
	char *p = (char *)&num;

	if (*p == 1)
		return (1);
	else
		return (0);
}
