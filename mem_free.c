#include "shell.h"

/**
 * free_all - free's all dynamically allocated memory
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void free_all(okeoma *oki)
{
	int i, k;

	free_recursive(oki->pos);
	free_list(oki->head);

	for (i = 0; oki->av[i] != NULL; i++)
		free(oki->av[i]);

	for (k = 0; oki->command[k] != NULL; k++)
		free(oki->command[k]);

	fr__(3, oki->cmd, oki->command, oki->av,
		oki->ok, oki->old, oki);
}

/**
 * fr__ - free count number of dynamically allocated memory
 * @count: number of memory to free
 *
 * Return: void
*/
void fr__(size_t count, ...)
{
	void *ptr;
	va_list args;
	size_t i;

	if (count <= 0)
	{
		p(STE, "Invalid number of arguments for fr__\n");
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
