#include "shell.h"

/**
 * sig - handler for the SIGINT signal
 * @num: signal to process
 *
 * Return: void 
*/
void sig(int num)
{
	v num;
	p(STO, "\n===> ");
	fflush(stdout);
}

/**
 * _in - initialise members of struct of type okeoma
 * @oki: struct of type okeoma
 * @argv: argument vector
 *
 * Return: Void 
*/
void _in(okeoma *oki, char **argv)
{
	oki->mypid = getpid();
	oki->cmd = NULL;
	oki->av = NULL;
	oki->command = NULL;
	oki->tok = NULL;
	oki->tok2 = NULL;
	oki->n = 0;
	oki->it = !isatty(STDIN_FILENO);
	oki->Name = argv[0];
	oki->com_num = 0;
	oki->i = 0;
	oki->head = list_from_env(environ);
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
	okeoma *oki = malloc(sizeof(okeoma));

	_in(oki, argv);
	signal(SIGINT, sig);
	if (!oki->it && argc == 1)
	{
		while (true)
		{
			oki->com_num++;
			p(STO, "===> ");
			oki->cmd = p_Input();
			if (oki->cmd == NULL || *oki->cmd == '\0')
			{
				free(oki->cmd);
				continue;
			}
			B_exc(oki);
		}
	}
	else
	{
		oki->cmd = p_Input();
		if (oki->cmd == NULL || *oki->cmd == '\0')
			free(oki->cmd);
		B_exc(oki);
	}
	return 0;
}
