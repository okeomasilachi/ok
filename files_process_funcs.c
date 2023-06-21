#include "main.h"

/**
 * open_file - opens a file for processing
 * @filename: name of file to open
 *
 * Return: the filediscriptor to the opened file
*/
int open_file(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		perror("open");
	return (fd);
}

/**
 * read_lines - reads the lines in a file to a buffer till the EOF characters
 * @fd: filedecriptor to read form
 *
 * Return: returns the chracters read
*/
char *read_lines(int fd)
{
	char *file_contents = NULL, buffer[BUFFER_SIZE];
	size_t file_size = 0;
	ssize_t bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		file_contents = realloc(file_contents, file_size + bytes_read + 1);
		if (file_contents == NULL)
		{
			close(fd);
			return (NULL);
		}
		memcpy(file_contents + file_size, buffer, bytes_read);
		file_size += bytes_read;
		bytes_read = read(fd, buffer, sizeof(buffer));
	}
	if (file_size > 0)
	{
		file_contents = realloc(file_contents, file_size + 1);
		if (file_contents == NULL)
		{
			close(fd);
			return (NULL);
		}
		file_contents[file_size] = '\0';
	}
	close(fd);
	return (file_contents);
}

/**
 * read_file - calls all file process in there order
 * @filename: file to call the processes on
 *
 * Return: the characters successfully read
*/
char *read_file(const char *filename)
{
	int fd;
	char *content;

	fd = open_file(filename);
	if (fd == -1)
		return (NULL);
	content = read_lines(fd);
	return (content);
}

/**
 * file - handles all processing that are file realted
 * @argv: argument varables
 * @oki: struct containing all parameters
 *
 * Return:void
*/
void file(okeoma *oki, char *argv)
{
	size_t read;

	oki->cmd = read_file(argv);
	read = strlen(oki->cmd);
	if (read > 0 && oki->cmd[read - 1] == '\n')
		oki->cmd[read - 1] = '\0';

	process(oki);
	exit(EXIT_SUCCESS);
}

void process(okeoma *oki)
{
	find_char(oki);
	oki->y = find_set(oki->cmd);
	f_tokenizer(&oki->tokens, oki->cmd);
	oki->tok2 = s_tok(&oki->tokens, "&&||");
	while (oki->tok2 != NULL)
	{
		prs_2(oki);
		for (oki->i = 0; oki->command[oki->i] != NULL; oki->i++)
		{
			prs(oki, oki->command[oki->i]);
			oki->com_num++;
			if ((oki->status = execute_builtin_command(oki)) != 0)
				oki->status = execute_command(oki);
		}
		if (oki->y == 1 && oki->status != 0)
			break;
		if (oki->y == 2 && oki->status == 0)
			break;
		oki->y = find_set(NULL);
		oki->tok2 = s_tok(&oki->tokens, "&&||");
	}
}
