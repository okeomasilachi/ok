#include "shell.h"

/**
 * find_char - searches for a chracter in string and return's
 * all characters before the speacified character
 * @dest: the string to be searched
 * @character: character to search for
 *
 * Return: Void
*/
void find_char(const char *dest, int character)
{
	char *str_cpy = strchr(dest, character);

	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
	}
}

/**
 * find_set - searches for "&& or ||" in a string
 * @str: the string to be searched
 *
 * Return: returns 1 if && is found
 * 2 is || is found, 0 if no match is found
*/
int find_set(char *str)
{
	static char *currentPosition;
	static int setValue;
	char *result1, *result2;

	if (str != NULL)
	{
		currentPosition = str;
		setValue = 0;
	}
	if (currentPosition == NULL)
		return (-1);

	result1 = "&&" != NULL ? strstr(currentPosition, "&&") : NULL;
	result2 = "||" != NULL ? strstr(currentPosition, "||") : NULL;
	if (result1 == NULL && result2 == NULL)
		return (-1);

	if (result1 == NULL || (result2 != NULL && result2 < result1))
	{
		currentPosition = result2 + strlen("||");
		setValue = 2;
	}
	else
	{
		currentPosition = result1 + strlen("&&");
		setValue = 1;
	}
	return (setValue);
}

/**
 * free_all - free's all dynamically allocated memory
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void free_all(okeoma *oki)
{
	int i, k;

	for (i = 0; oki->av[i] != NULL; i++)
		free(oki->av[i]);

	for (k = 0; oki->command[k] != NULL; k++)
		free(oki->command[k]);

	my_free(3, oki->cmd, oki->command, oki->av);
}

/**
 * my_free - free count number of dynamically allocated memory
 * @count: number of memory to free
 *
 * Return: void
*/
void my_free(size_t count, ...)
{
	void *ptr;
	va_list args;
	size_t i;

	if (count <= 0)
	{
		p(STE, "Invalid number of arguments for my_free\n");
		return;
	}
	va_start(args, count);
	for (i = 0; i < count; i++)
	{
		ptr = va_arg(args, void *);

		if (ptr != NULL)
			free(ptr);
		else
			continue;
	}
	va_end(args);
}
