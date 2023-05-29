#include "main.h"


void read_in(okeoma *info)
{
	ssize_t read_bytes;
	int input_length, write_index = 0, space_count = 0, i, newline_count;

	info->cmd = (char *)malloc(BUFFER_SIZE * sizeof(char));
	read_bytes = read(STDIN_FILENO, info->cmd, BUFFER_SIZE);
	input_length = read_bytes;
	write_index = 0, space_count = 0;
	for (i = 0; i < input_length; i++)
	{
		if (isspace(info->cmd[i]))
			space_count++;
		else
			space_count = 0;

		if (space_count <= 1)
			info->cmd[write_index++] = info->cmd[i];
	}
	newline_count = 0;
	for (i = 0; i < write_index; i++)
	{
		if (info->cmd[i] == '\n')
			newline_count++;
		else
		{
			if (newline_count > 1)
			{
				info->cmd[i - newline_count + 1] = ';';
				write_index = write_index - (newline_count - 1);
			}
			newline_count = 0;
		}
	}
	if (newline_count > 1)
	{
		info->cmd[write_index - newline_count + 1] = ';';
		write_index = write_index - (newline_count - 1);
	}
	info->cmd[write_index] = '\0';
	info->cmd = (char*)realloc(info->cmd, (write_index + 1) * sizeof(char));
}