#include "shell.h"

/**
 * checker - checks if the "$" character if in a string
 * @arr: pointer to the string to be checked
 *
 * Return: true if match is found else fales is returned
*/
bool checker(char *arr)
{
	if (arr == NULL)
		return (false);
	else if (strstr(arr, "$") != NULL)
		return (true);
	else
		return (false);
}

/**
 * r_char - converst an int to a char
 * @value: the interger to be converted
 * @str: a pointer to the character after convertion
 * @base: base to convertion to
 *
 * Return: Void
*/
void r_char(int value, char *str, int base)
{
	int i, is_neg, rem, len, st, ed;
	char temp;

	if (value == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	i = 0;
	is_neg = 0;

	if (value < 0 && base == 10)
	{
		is_neg = 1;
		value = -value;
	}
	while (value != 0)
	{
		rem = value % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		value /= base;
	}
	if (is_neg)
		str[i++] = '-';

	str[i] = '\0';
	len = _strlen(str);
	st = 0;
	ed = len - 1;
	while (st < ed)
	{
		temp = str[st];
		str[st] = str[ed];
		str[ed] = temp;
		st++;
		ed--;
	}
}

/**
 * int_char - converts two integers to character
 * @n1: first integer to be converted
 * @n2: second integer to be converted
 * @str: pointer to an array for storing the converted integers
 *
 * Return:
*/
void int_char(int n1, int n2, char **str)
{
	str[0] = malloc(20);
	str[1] = malloc(20);

	r_char(n1, str[0], 10);
	r_char(n2, str[1], 10);
}
