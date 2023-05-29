#include "main.h"


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
	oki->cmd = (char*)realloc(oki->cmd, (write_index + 1) * sizeof(char));
}


void find_char(okeoma *oki)
{
	char *str_cpy = strchr(oki->cmd, '#');

	if (str_cpy != NULL)
	{
		*str_cpy = '\0';
	}
}

void f_set(okeoma *oki, char *str)
{
	static char *currentPosition;
	char *result1, *result2;

	if (str != NULL)
	{
		currentPosition = str;
		oki->y = 0;
	}
	if (currentPosition == NULL)
	{
		dprintf(STDERR_FILENO, "Invalid input. Please provide a string to search.\n");
	}
	result1 = "&&" != NULL ? strstr(currentPosition, "&&") : NULL;
	result2 = "||" != NULL ? strstr(currentPosition, "||") : NULL;
	if (result1 == NULL && result2 == NULL)
		oki->y = -1;

	if (result1 == NULL || (result2 != NULL && result2 < result1))
	{
		currentPosition = result2 + strlen("||");
		oki->y = 2;
	}
	else
	{
		currentPosition = result1 + strlen("&&");
		oki->y = 1;
	}
}
