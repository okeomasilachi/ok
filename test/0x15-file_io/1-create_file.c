#include "main.h"

/**
 * create_file - creates a file
 * @filename: name of the file to create
 * @text_content: NULL terminated string to write to the file
 *
 * Return: On success 1, on error 0
*/

int create_file(const char *filename, char *text_content)
{
	int fl;
	ssize_t wrt;

	if (filename == NULL)
		return (-1);

	fl = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fl == -1)
		return (-1);

	if (text_content != NULL)
	{
		wrt = write(fl, text_content, strlen(text_content));
		if (wrt == -1)
		{
			close(fl);
			return (-1);
		}
	}
	close(fl);
	return (1);
}
