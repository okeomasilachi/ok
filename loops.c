#include "main.h"

/**
 * non_loop - shell interactive loop
 * @av: argument count
 * @command: argument count
 * @command_count: command number
 * @fd: file stream
 * @status: exit status
 * @argv: argument vector
 * @colon: for the command separator
 *
 * Return: void
*/
void non_loop(char **av, char *command, size_t command_count,
FILE *fd, int status, char **argv, char **colon)
{
	ssize_t byte_r;
	size_t n = 0;
	char st = !isatty(STDIN_FILENO);

	v av;

	do {
		byte_r = getline(&command, &n, fd);
		if (byte_r != -1)
		{
			remov(command);
			line(command);
			if (empty(command))
			{
				command_count++;
				continue;
			}
			if (*command == '\n')
				continue;
			handel_comment(command);
			command_count++;
			if (*command != '\0')
				exec(command, av, argv, command_count, st, status, colon);

			if (st)
				continue;
			if (!st)
				break;
		}
	} while (byte_r != -1);
	exit(status);
}

/**
 * _loop - shell interactive loop
 * @argc: argument count
 * @av: argument count
 * @command: argument count
 * @command_count: command number
 * @fd: file stream
 * @status: exit status
 * @argv: argument vector
 * @colon: for the command separator
 *
 * Return: void
*/
void _loop(int argc, char **av, char *command, size_t command_count,
FILE *fd, int status, char **argv, char **colon)
{
	ssize_t byte_r;
	size_t n = 0;
	char st = !isatty(STDIN_FILENO);

	v av;

	while (true && isatty(STDIN_FILENO) && (!st || byte_r != 0))
	{
		command_count++;
		st = !isatty(STDIN_FILENO);
		if (argc == 1 && !st)
			print(STO, "$ ");
		byte_r = getline(&command, &n, fd);
		if (byte_r == -1)
		{
			free(command);
			print(STO, "\n");
			break;
		}
		line(command);
		remov(command);
		if (empty(command))
		{
			continue;
		}
		if (*command == '\n')
			continue;
		handel_comment(command);
		if (*command != '\0')
			exec(command, av, argv, command_count, st, status, colon);
		if (!st)
			continue;
		if (st)
			break;
	}
}
