#include "main.h"

void _in(okeoma *oki, char **argv)
{
	oki->cmd = NULL;
	oki->av = NULL;
	oki->command = NULL;
	oki->tok = NULL;
	oki->tok2 = NULL;
	oki->n = 0;
	oki->it = isatty(STDIN_FILENO);
	oki->Name = argv[0];
	oki->com_num = 0;
	oki->i = 0;
	oki->head = NULL;

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
 * prs - parses input command to tokens
 * @command: command to be parsed
 * @del_n: sets delimiter to requirments
 *
 * Return: pointer the array of parsed commands
 * error: NULL
*/
void prs(okeoma *oki, char *coms)
{
	char *com_cpy = NULL, *dl = " \t\n\r";
	size_t count = 0, cnt = 0;

	if (oki->cmd)
	{
		com_cpy = strdup(coms);
		f_tokenizer(&oki->baxi, coms);
		oki->tok = s_tok(&oki->baxi, dl);
		while (oki->tok)
		{
			cnt++;
			oki->tok = s_tok(&oki->baxi, dl);
		}
		cnt++;
		oki->av = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(&oki->baxi, com_cpy);
		oki->tok = s_tok(&oki->baxi, dl);
		while (oki->tok)
		{
			oki->av[count] = malloc(sizeof(char) * (strlen(oki->tok) + 1));
			strcpy(oki->av[count], oki->tok);
			oki->tok = s_tok(&oki->baxi, dl);
			count++;
		}
		oki->av[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}

int execute_command(okeoma *oki)
{
	oki->ec = find_executable(oki);
	if (!oki->ec)
	{
		p(STE, "%s: %d: %s: not found\n", oki->Name, oki->com_num, oki->av[0]);
	}
	if (oki->ec)
	{
		oki->child_pid = fork();
		if (oki->child_pid == -1)
			perror("fork");

		else if (oki->child_pid == 0)
		{
			execve(oki->ec, oki->av, environ);
			perror("execve");
			return (EXIT_FAILURE);
		}
		else
		{
			waitpid(oki->child_pid, &oki->status, 0);
			free(oki->ec);
			if (WIFEXITED(oki->status))
			{
				return (WEXITSTATUS(oki->status));
			}
		}
	}
	return (-1);
}
