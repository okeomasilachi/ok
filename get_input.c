#include "shell.h"

/**
 * read_input - reads input from a buffer
 *
 * @buffer: Pointer to the buffer
 * @buffer_pos: Pointer to the buffer position
 * @buffer_size: Pointer to the buffer size
 *
 * Return: void
 */
void read_input(char *buffer, int *buffer_pos, int *buffer_size)
{
	fflush(stdout);

	if (*buffer_pos >= *buffer_size)
	{
		*buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (*buffer_size == -1)
			exit(EXIT_FAILURE);

		if (*buffer_size == 0)
		{
			p(STO, "\n");
			exit(EXIT_SUCCESS);
		}
		*buffer_pos = 0;
	}
}

/**
 * _getline - reads a line from a buffer
 *
 * @buffer: Pointer to the buffer
 * @buffer_pos: Pointer to the buffer position
 * @buffer_size: Pointer to the buffer size
 *
 * Return: Pointer to the read line
 */
char *_getline(char *buffer, int *buffer_pos, int *buffer_size)
{
	char *line = NULL;
	int line_size = 0;

	while (true)
	{
		if (*buffer_pos >= *buffer_size)
			read_input(buffer, buffer_pos, buffer_size);

		if (buffer[*buffer_pos] == '\n')
		{
			(*buffer_pos)++;
			line = realloc(line, line_size + *buffer_pos);
			memcpy(line + line_size, buffer, *buffer_pos);
			line_size += *buffer_pos;
			line[line_size - 1] = '\0';
			return (line);
		}
		(*buffer_pos)++;
	}
	if (line != NULL)
	{
		line = realloc(line, line_size + *buffer_pos);
		memcpy(line + line_size, buffer, *buffer_pos);
		line_size += *buffer_pos;
		line[line_size - 1] = '\0';
	}
	return (line);
}

/**
 * p_Input - call all functions for reading from stdin
 *
 * Return: pointer to the read characters
*/
void *p_Input()
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos, buffer_size;
	char *m;

	read_input(buffer, &buffer_pos, &buffer_size);
	m = _getline(buffer, &buffer_pos, &buffer_size);
	return (m);
}

/**
 * read_in - reads from stdin to a buffer
 * @oki: structure containing all parameters
 *
 * Return: Void
*/
void read_in(okeoma *oki)
{
	ssize_t read_bytes;
	int input_length, write_index = 0, space_count = 0, i, newline_count;

	oki->cmd = (char *)malloc(BUFFER_SIZE * sizeof(char));
	read_bytes = read(STDIN_FILENO, oki->cmd, BUFFER_SIZE);
	input_length = read_bytes;
	write_index = 0, space_count = 0;
	for (i = 0; i < input_length; i++)
	{
		if (isspace(oki->cmd[i]))
			space_count++;
		else
			space_count = 0;

		if (space_count <= 1)
			oki->cmd[write_index++] = oki->cmd[i];
	}
	newline_count = 0;
	for (i = 0; i < write_index; i++)
	{
		if (oki->cmd[i] == '\n')
			newline_count++;
		else
		{
			if (newline_count > 1)
			{
				oki->cmd[i - newline_count + 1] = ';';
				write_index = write_index - (newline_count - 1);
			}
			newline_count = 0;
		}
	}
	if (newline_count > 1)
	{
		oki->cmd[write_index - newline_count + 1] = ';';
		write_index = write_index - (newline_count - 1);
	}
	oki->cmd[write_index] = '\0';
	oki->cmd = (char *)realloc(oki->cmd, (write_index + 1) * sizeof(char));
}
