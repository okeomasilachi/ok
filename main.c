#include "main.h"

/**
 * sig - handler for the SIGINT signal
 * @num: signal to process
 *
 * Return: void
*/
void sig(int num)
{
	v num;

	print(STO, "\n$ ");
	fflush(stdout);
}

/**
 * main - entry point of the shell
 * @argc: argument count
 * @argv: argument vectors
 *
 * Return: 0 on success
 * error: Non zero value is returned
*/
int main(int argc, char **argv)
{
	char **av = NULL, **colon = NULL, *command = NULL;
	size_t n = 0, command_count = 0;
	ssize_t byte_r = 1;
	char st = 0;
	int status = 0;

	v status, v st, v byte_r, v n;

	signal(SIGINT, sig);
	if (!isatty(STDIN_FILENO))
	{
		non_loop(av, command, command_count, stdin, status, argv, colon);
	}
	if (isatty(STDIN_FILENO) && argc == 1)
		_loop(argc, av, command, command_count, stdin, status, argv, colon);

	return (0);
}
