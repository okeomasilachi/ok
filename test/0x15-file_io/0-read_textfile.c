#include "main.h"

/**
 * read_textfile - reads and prints to stdout a particular number of byte
 * @filename: file to read from
 * @letters: number of bytes to read and written
 *
 * Return: on success number of bytes written
 * error 0
*/

ssize_t read_textfile(const char *filename, size_t letters)
{
	ssize_t Bw, Br;
	int fd;
	char *oki;

	if (filename == NULL)
		return (0);

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	oki = malloc(sizeof(char) * letters);
	if (oki == NULL)
	{
		close(fd);
		return (0);
	}
	Br = read(fd, oki, letters);
	if (Br == -1)
	{
		free(oki);
		close(fd);
		return (0);
	}
	Bw = write(STDOUT_FILENO, oki, Br);
	if (Bw == -1 || Bw != Br)
	{
		free(oki);
		close(fd);
		return (0);
	}
	free(oki);
	close(fd);
	return (Bw);
}
