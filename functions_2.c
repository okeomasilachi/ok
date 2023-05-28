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
void B_exc(okeoma *info)
{
	int i;

	prs_2(info, 1);
	for (i = 0; info->command[i] != NULL; i++)
	{
		prs(info, 0);
		info->status = execute_builtin_command(info);
		if (info->status != 0)
			info->status = execute_command(info);
	}
}

void prs_2(okeoma *info, size_t del_n)
{
	char *com_cpy = NULL, *dl = NULL;
	size_t count = 0, cnt = 0;

	if (del_n == 0)
		dl = " \t\n\r";

	if (del_n == 1)
		dl = ";\n";

	if (info->cmd)
	{
		com_cpy = strdup(info->cmd);
		f_tokenizer(info, info->cmd);
		info->tok = s_tok(info, dl);
		while (info->tok)
		{
			cnt++;
			info->tok = s_tok(info, dl);
		}
		cnt++;
		info->command = malloc(sizeof(char *) * (cnt + 1));
		f_tokenizer(info, com_cpy);
		info->tok = s_tok(info, dl);
		while (info->tok)
		{
			info->command[count] = malloc(sizeof(char) * (strlen(info->tok) + 1));
			strcpy(info->command[count], info->tok);
			info->tok = s_tok(info, dl);
			count++;
		}
		info->command[count] = NULL;
		free(com_cpy);
		com_cpy = NULL;
		count = 0, cnt = 0;
	}
}

char *env_pos(okeoma *info)
{
	int name_len;
	char **env, *env_var;

	if (info->av[1] == NULL || *info->av[1] == '\0')
		return (NULL);

	name_len = strlen(info->av[1]);
	for (env = environ; *env != NULL; env++)
	{
		env_var = *env;
		if (env_var == NULL || *env_var == '\0' || strchr(env_var, '=') == NULL)
			continue;
		if (strncmp(info->av[1], env_var, name_len) == 0 && env_var[name_len] == '=')
			return (&(env_var[name_len - name_len]));
	}
	return (NULL);
}

void free_all(okeoma *info)
{
	int i, k;

	for (i = 0; info->av[i] != NULL; i++)
	{
		free(info->av[i]);
	}
	for (k = 0; info->command[k] != NULL; k++)
	{
		free(info->command[k]);
	}
	_fee(4, info->cmd, info->av, info->command, info);
}

/**
 * _free - free n number of dynamically allocated memory
 * @count: number of memory to free
 *
 * Return: void
*/
void _fee(int count, ...)
{
	void *ptr;
	va_list args;
	int i;

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
