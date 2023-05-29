#include "main.h"

/**
 * B_exc - function handles all command processing
 * @argc: argument count
 * @N: name of the compiled program [argv[0]]
 * @cmd: commandline input
 * @av: parsed commands
 * @env: environmental variable
 * @ok: command number
 *
 * Return: void
*/
void B_exc(okeoma *oki)
{
	prs_2(oki);
	for (oki->i = 0; oki->command[oki->i] != NULL; oki->i++)
	{
		prs(oki, oki->command[oki->i]);
		if (!oki->it)
			oki->com_num++;
		oki->status = execute_builtin_command(oki);
		if (oki->status != 0)
			oki->status = execute_command(oki);
	}
}

void prs_2(okeoma *oki)
{
	char *com_cpy = NULL, *dl = dl = ";\n";
	size_t count = 0, cnt = 0;

	if (oki->cmd)
	{
		com_cpy = strdup(oki->cmd);
		f_tokenizer(oki, oki->cmd);
		oki->tok = s_tok(oki, dl);
		while (oki->tok)
		{
			cnt++;
			oki->tok = s_tok(oki, dl);
		}
		cnt++;
		oki->command = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(oki, com_cpy);
		oki->tok = s_tok(oki, dl);
		while (oki->tok)
		{
			oki->command[count] = malloc(sizeof(char) * (strlen(oki->tok) + 1));
			strcpy(oki->command[count], oki->tok);
			oki->tok = s_tok(oki, dl);
			count++;
		}
		oki->command[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}

char *env_pos(okeoma *oki)
{
	int name_len;
	char **env, *env_var;

	if (oki->av[1] == NULL || *oki->av[1] == '\0')
		return (NULL);

	name_len = strlen(oki->av[1]);
	for (env = environ; *env != NULL; env++)
	{
		env_var = *env;
		if (env_var == NULL || *env_var == '\0' || strchr(env_var, '=') == NULL)
			continue;
		if (strncmp(oki->av[1], env_var, name_len) == 0 && env_var[name_len] == '=')
			return (&(env_var[name_len - name_len]));
	}
	return (NULL);
}

void free_all(okeoma *oki)
{
	int i, k;

	for (i = 0; oki->av[i] != NULL; i++)
	{
		free(oki->av[i]);
	}
	for (k = 0; oki->command[k] != NULL; k++)
	{
		free(oki->command[k]);
	}
	my_free(4, oki->cmd, oki->av, oki->command, oki);
}

/**
 * _free - free n number of dynamically allocated memory
 * @count: number of memory to free
 *
 * Return: void
*/
void my_free(size_t count, ...)
{
	void *ptr;
	va_list args;
	size_t i;

	if (count <= 0)
	{
		dprintf(STDERR_FILENO, "Invalid number of arguments for _free.\n");
		return;
	}
	va_start(args, count);
	for (i = 0; i < count; i++)
	{
		ptr = va_arg(args, void *);

		if (ptr != NULL)
			free(ptr);
		else
			dprintf(STDERR_FILENO, "NULL pointer encountered in _free.\n");
	}
	va_end(args);
}
