#include "main.h"

/**
 * main - entry point of program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: on success 0
*/

int main(int ac, char **av)
{
	int ff, ft, ftc, ffc;
	char *buf;
	ssize_t nr, nw;

	if (ac != 3)
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n"), exit(97);

	ft = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	ff = open(av[1], O_RDONLY);
	buf = malloc(BUF_OKI);
	while ((nr = read(ff, buf, BUF_OKI)) > 0)
		nw = write(ft, buf, nr);

	if (nr == -1 || ff == -1)
	{
		close(ft);
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", av[1]), exit(98);
	}
	if (nw == -1 || ft == -1)
	{
		close(ff);
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", av[2]), exit(99);
	}
	free(buf);
	ffc = close(ff), ftc = close(ft);
	if (ffc == -1 || ftc == -1)
	{
		if (ffc == -1)
			dprintf(STDERR_FILENO, "Error: Can't close fd 1");
		else
			dprintf(STDERR_FILENO, "Error: Can't close fd 2");
		exit(100);
	}
	exit(EXIT_SUCCESS);
}
