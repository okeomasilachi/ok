#include "main.h"

/**
 * append_text_to_file - append content to a file
 * @filename: name of file to append text to
 * @text_content: text to append tothe file
 *
 * Return: On success 1
 * error -1
*/

int append_text_to_file(const char *filename, char *text_content)
{
	ssize_t wt;
	int ap;

	if (filename == NULL)
		return (-1);

	ap = open(filename, O_WRONLY | O_APPEND);
	if (ap == -1)
		return (-1);

	if (text_content != NULL)
	{
		wt = write(ap, text_content, strlen(text_content));
		if (wt == -1)
		{
			close(ap);
			return (-1);
		}
	}
	close(ap);
	return (1);
}
