#include "main.h"

void _in(okeoma *info, char **argv)
{
	info->cmd = NULL;
	info->av = NULL;
	info->tok = NULL;
	info->n = 0;
	info->it = isatty(STDIN_FILENO);
	info->Name = argv[0];
	info->com_num = 0;
	info->i = 0;
}

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
			putchar('\n');
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
 * prs - parses input command to tokens
 * @command: command to be parsed
 * @del_n: sets delimiter to requirments
 *
 * Return: pointer the array of parsed commands
 * error: NULL
*/
void prs(okeoma *info, char *coms)
{
	char *com_cpy = NULL, *dl = " \t\n\r";
	size_t count = 0, cnt = 0;

	if (info->cmd)
	{
		com_cpy = strdup(coms);
		f_tokenizer(info, coms);
		info->tok = s_tok(info, dl);
		while (info->tok)
		{
			cnt++;
			info->tok = s_tok(info, dl);
		}
		cnt++;
		info->av = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(info, com_cpy);
		info->tok = s_tok(info, dl);
		while (info->tok)
		{
			info->av[count] = malloc(sizeof(char) * (strlen(info->tok) + 1));
			strcpy(info->av[count], info->tok);
			info->tok = s_tok(info, dl);
			count++;
		}
		info->av[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}

int execute_command(okeoma *info)
{
	
	info->ec = find_executable(info);
	if (!info->ec)
	{
		dprintf(STDERR_FILENO, "%s: %ld: %s: not found\n", info->Name, info->com_num, info->av[0]);
	}
	if (info->ec)
	{
		info->child_pid = fork();
		if (info->child_pid == -1)
			perror("fork");

		else if (info->child_pid == 0)
		{
			execve(info->ec, info->av, environ);
			return (EXIT_FAILURE);
		}
		else
		{
			waitpid(info->child_pid, &info->status, 0);
			free(info->ec);
			if (WIFEXITED(info->status))
			{
				return (WEXITSTATUS(info->status));
			}
		}
	}
	return (-1);
}
