#include "shell.h"

/**
 * var_free - frees all char ** variables
 * @oki: struct of type okeoma
 *
 * Return: void
*/
void var_free(okeoma *oki)
{
	int i;

	for (i = 0; oki->av[i] != NULL; i++)
		free(oki->av[i]);

	for (i = 0; oki->command[i] != NULL; i++)
		free(oki->command[i]);
	free(oki->command);
	free(oki->av);
}

/**
 * file_loop - shell interactive loop
 * @oki: struct of type okeoma
 * @n: buffer size for getline
 * @byte_r: actual bytes read by getline
 * @st: file stream check
 * @fd: file stream
 *
 * Return: void
*/
void file_loop(okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd)
{
	st = isatty(STDIN_FILENO);
	byte_r = 0;
	do {
		oki->c++;
		while ((byte_r = getline(&oki->cmd, &n, fd)) != -1)
		{
			remov(oki->cmd);
			line(oki->cmd);

			if (empty(oki->cmd))
			{
				oki->c++;
				continue;
			}
			if (oki->cmd == NULL || *oki->cmd == '\0')
				break;
			if (*oki->cmd == '\n')
				break;
			B_exc(oki);
			var_free(oki);
			if (oki->it && !st)
				continue;
			if (!oki->it && st)
				break;
		}
	} while (byte_r != -1);
}


/**
 * non_loop - shell interactive loop
 * @oki: struct of type okeoma
 * @n: buffer size for getline
 * @byte_r: actual bytes read by getline
 * @st: file stream check
 * @fd: file stream
 *
 * Return: void
*/
void non_loop(okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd)
{
	st = !isatty(STDIN_FILENO);
	do {
		byte_r = getline(&oki->cmd, &n, fd);
		if (byte_r != -1)
		{
			remov(oki->cmd);
			line(oki->cmd);
			if (empty(oki->cmd))
			{
				oki->c++;
				continue;
			}
			if (*oki->cmd == '\n')
				continue;
			B_exc(oki);
			if (oki->it && !st)
				continue;
			if (!oki->it && st)
				break;
		}
	} while (byte_r != -1);
}


/**
 * _loop - shell interactive loop
 * @argc: argument count
 * @oki: struct of type okeoma
 * @n: buffer size for getline
 * @byte_r: actual bytes read by getline
 * @st: file stream check
 * @fd: file stream
 *
 * Return: void
*/
void _loop(int argc, okeoma *oki, size_t n, ssize_t byte_r, char st, FILE *fd)
{
	while (true && isatty(STDIN_FILENO) && (!st || byte_r != 0))
	{
		if (!st && !oki->it)
			oki->c++;
		st = !isatty(STDIN_FILENO);
		if (argc == 1 && !st && !oki->it)
			p(STO, "$ ");
		byte_r = getline(&oki->cmd, &n, fd);
		if (byte_r == -1)
		{
			putchar('\n');
			break;
		}
		line(oki->cmd);
		remov(oki->cmd);
		if (empty(oki->cmd))
		{
			oki->c++;
			continue;
		}
		if (*oki->cmd == '\n')
			continue;
		B_exc(oki);
		var_free(oki);
		if (!oki->it && !st)
			continue;
		if (oki->it && st)
			break;
	}
}
