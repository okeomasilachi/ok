#include "shell.h"

/**
 * _memcpy - copies the memory address of a string
 * @dest: destination of the copied address
 * @src: the string memory to be copied
 * @n: number of bytes to copy
 *
 * Return: void
*/
void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *destination;
	const unsigned char *source;

	if (dest == NULL || src == NULL)
		return (NULL);

	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;
	if (destination == source)
		return (dest);

	for (i = 0; i < n; i++)
		destination[i] = source[i];

	return (dest);
}


/**
 * _memmove - moves a memory address
 * @dest: destination to move to
 * @src: string to move from
 * @n: number of bytes to move
 *
 * Return: void
*/
void *_memmove(void *dest, const void *src, size_t n)
{
	unsigned char *destination;
	const unsigned char *source;
	size_t i;

	if (dest == NULL || src == NULL)
		return (NULL);

	destination = (unsigned char *)dest;
	source = (const unsigned char *)src;

	if (destination == source)
		return (dest);

	if (destination < source)
	{
		for (i = 0; i < n; i++)
			destination[i] = source[i];
	}
	else
	{
		for (i = n; i > 0; i--)
			destination[i - 1] = source[i - 1];
	}
	return (dest);
}


/**
 * _atoi - converts string to integer
 * @nptr: string to be converted
 *
 * Return: void
*/
int _atoi(const char *nptr)
{
	int result, sign, i, digit;

	if (nptr == NULL)
		return (0);

	result = 0;
	sign = 1;
	i = 0;

	while (_isspace(nptr[i]))
		i++;

	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign = (nptr[i] == '-') ? -1 : 1;
		i++;
	}
	while (_isdigit(nptr[i]))
	{
		digit = nptr[i] - '0';
		if (result > (INT_MAX - digit) / 10)
			return (sign == 1 ? INT_MAX : INT_MIN);
		result = result * 10 + digit;
		i++;
	}
	return (sign * result);
}

/**
 * _realloc - reallocates memory for a buffer
 * @ptr: memory to reallocate
 * @size: size to reallocate
 *
 * Return: pointer to newly allocated memory
 * error: NULL
*/
void *_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));

	new_ptr = malloc(size);
	if (new_ptr == NULL)
		return (NULL);

	_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

/**
 * _strcpy - copies string
 *
 * @dest: updatd string
 * @src: string copy
 *
 * Return: returns dest
 */

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
