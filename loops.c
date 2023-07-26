#include "shell.h"

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
	v byte_r;

	while (true)
	{
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
			if (oki->it && !st)
				continue;
			if (/* !oki->it  */st)
				break;
		}
	}
	free_all(oki);
	putchar('\n');
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
	while (true)
	{
		st = !isatty(STDIN_FILENO);
		while ((byte_r = getline(&oki->cmd, &n, fd)) != -1)
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
			oki->c++;
		}
	}
	free_all(oki);
	putchar('\n');
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
		line(oki->cmd);
		remov(oki->cmd);
		if (empty(oki->cmd))
		{
			oki->c++;
			continue;
		}
		if (*oki->cmd == '\n')
			continue;
		if (*oki->cmd == EOF)
			break;
		if (byte_r == -1)
			break;
		B_exc(oki);
		if (!oki->it && !st)
			continue;
		if (oki->it && st)
			break;
		oki->c++;
	}
}
