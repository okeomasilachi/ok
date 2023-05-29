#include "main.h"

/**
 * f_tokenizer - the initializer for string tokenization
 * @tokenizer: struct for storing the tokens
 * @input_string: string to tokenize
 *
 * Return: void
*/
void f_tokenizer(okeoma *info, char *cm)
{
	info->tokens.cur_tok_st = cm;
	info->tokens.nxt_tok_st = cm;
}

/**
 * s_tok - function for tokenizing strings
 * @tokenizer: struct where token are stored
 * @delimiters: the delimeters for the tokenization
 *
 * Return: pointer to token
 * error: NULL if no more tokens are found
*/
char *s_tok(okeoma *info, const char *delimiters)
{
	char *token;

	if (info->tokens.cur_tok_st == NULL)
		return (NULL);
	/* Skip leading delimiters */
	info->tokens.cur_tok_st += strspn(info->tokens.cur_tok_st, delimiters);
	/* Check if end of string is reached */
	if (*info->tokens.cur_tok_st == '\0')
	{
		info->tokens.cur_tok_st = NULL;
		return (NULL);
	}
	info->tokens.nxt_tok_st = info->tokens.cur_tok_st;
	/* Find the end of the current token */
	info->tokens.nxt_tok_st += strcspn(info->tokens.nxt_tok_st, delimiters);
	if (*info->tokens.nxt_tok_st != '\0')
	{
		*info->tokens.nxt_tok_st = '\0';
		info->tokens.nxt_tok_st++;
	}
	else
	{
		info->tokens.nxt_tok_st = NULL;
	}
	token = info->tokens.cur_tok_st;
	info->tokens.cur_tok_st = info->tokens.nxt_tok_st;

	return (token);
}

char *find_executable(okeoma *info)
{
	char *path_env, *path_copy, *token, *exe_path;
	size_t token_len, exec_name_len;

	if (access(info->av[0], X_OK) == 0)
	{
		exe_path = strdup(info->av[0]);
		return (exe_path);
	}
	path_env = getenv("PATH");
	path_copy = strdup(path_env);
	f_tokenizer(info, path_copy);
	token = s_tok(info, ":");
	while (token)
	{
		token_len = strlen(token);
		exec_name_len = strlen(info->av[0]);
		exe_path = (char *)malloc((token_len + exec_name_len + 2) * sizeof(char));
		if (exe_path == NULL)
		{
			perror("Memory allocation failed");
			free(path_copy);
			return (NULL);
		}
		strcpy(exe_path, token);
		strcat(exe_path, "/");
		strcat(exe_path, info->av[0]);
		if (access(exe_path, X_OK) == 0)
		{
			free(path_copy);
			return (exe_path);
		}
		free(exe_path);
		token = s_tok(info, ":");
	}
	free(path_copy);
	return (NULL);
}


void interactive(okeoma *info)
{
	while (true)
	{
		info->com_num++;
		printf("===> ");
		info->cmd = p_Input();
		if (info->cmd == NULL || *info->cmd == '\0')
		{
			free(info->cmd);
			continue;
		}
		B_exc(info);
		for (info->i = 0; info->av[info->i] != NULL; info->i++)
			free(info->av[info->i]);
	
		free(info->av);
	}
}

void non_interactive(okeoma *info)
{
	info->cmd = read_in();
	if (info->cmd == NULL || *info->cmd == '\0')
		free(info->cmd);

	B_exc(info);
	
}

/**
 * execute_builtin_command - this function runs built-in
 * @args: arguments to pass to the command
 * @NAME: name of the compiled program
 * @num: argument count
 *
 * Return: 0 on success
 * error: 1 on error
*/
int execute_builtin_command(okeoma *info)
{
	char *built_in_commands[] = {
		"cd",
		"exit",
		"setenv",
		"unsetenv",
		"help"
	};

	void (*built_in_funcs[])(okeoma *info) = {
		&cd_command,
		&exit_command,
		&setenv_command,
		&unsetenv_command,
		&help_command
	};
	int num_built_in_com = sizeof(built_in_commands) / sizeof(char *), i;

	for (i = 0; i < num_built_in_com; i++)
	{
		if (strcmp(info->av[0], built_in_commands[i]) == 0)
		{
			(*built_in_funcs[i])(info);
			return (0); /* Command executed */
		}
	}
	return (1); /* Not a built-in command */
}