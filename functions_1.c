#include "main.h"

/**
 * f_tokenizer - the initializer for string tokenization
 * @tokenizer: struct for storing the tokens
 * @input_string: string to tokenize
 *
 * Return: void
*/
void f_tokenizer(okeoma *oki, char *cm)
{
	oki->tokens.cur_tok_st = cm;
	oki->tokens.nxt_tok_st = cm;
}

/**
 * s_tok - function for tokenizing strings
 * @tokenizer: struct where token are stored
 * @delimiters: the delimeters for the tokenization
 *
 * Return: pointer to token
 * error: NULL if no more tokens are found
*/
char *s_tok(okeoma *oki, const char *delimiters)
{
	char *token;

	if (oki->tokens.cur_tok_st == NULL)
		return (NULL);
	/* Skip leading delimiters */
	oki->tokens.cur_tok_st += strspn(oki->tokens.cur_tok_st, delimiters);
	/* Check if end of string is reached */
	if (*oki->tokens.cur_tok_st == '\0')
	{
		oki->tokens.cur_tok_st = NULL;
		return (NULL);
	}
	oki->tokens.nxt_tok_st = oki->tokens.cur_tok_st;
	/* Find the end of the current token */
	oki->tokens.nxt_tok_st += strcspn(oki->tokens.nxt_tok_st, delimiters);
	if (*oki->tokens.nxt_tok_st != '\0')
	{
		*oki->tokens.nxt_tok_st = '\0';
		oki->tokens.nxt_tok_st++;
	}
	else
	{
		oki->tokens.nxt_tok_st = NULL;
	}
	token = oki->tokens.cur_tok_st;
	oki->tokens.cur_tok_st = oki->tokens.nxt_tok_st;

	return (token);
}

char *find_executable(okeoma *oki)
{
	char *path_env, *path_copy, *token, *exe_path;
	size_t token_len, exec_name_len;

	if (access(oki->av[0], X_OK) == 0)
	{
		exe_path = strdup(oki->av[0]);
		return (exe_path);
	}
	path_env = getenv("PATH");
	path_copy = strdup(path_env);
	f_tokenizer(oki, path_copy);
	token = s_tok(oki, ":");
	while (token)
	{
		token_len = strlen(token);
		exec_name_len = strlen(oki->av[0]);
		exe_path = (char *)malloc((token_len + exec_name_len + 2) * sizeof(char));
		if (exe_path == NULL)
		{
			perror("Memory allocation failed");
			free(path_copy);
			return (NULL);
		}
		strcpy(exe_path, token);
		strcat(exe_path, "/");
		strcat(exe_path, oki->av[0]);
		if (access(exe_path, X_OK) == 0)
		{
			free(path_copy);
			return (exe_path);
		}
		free(exe_path);
		token = s_tok(oki, ":");
	}
	free(path_copy);
	return (NULL);
}


void interactive(okeoma *oki)
{
	while (true)
	{
		oki->com_num++;
		printf("===> ");
		oki->cmd = p_Input();
		if (oki->cmd == NULL || *oki->cmd == '\0')
		{
			free(oki->cmd);
			continue;
		}
		B_exc(oki);
		for (oki->i = 0; oki->av[oki->i] != NULL; oki->i++)
			free(oki->av[oki->i]);
	
		free(oki->av);
	}
}

void non_interactive(okeoma *oki)
{
	read_in(oki);
	if (oki->cmd == NULL || *oki->cmd == '\0')
		free(oki->cmd);

	B_exc(oki);
	
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
int execute_builtin_command(okeoma *oki)
{
	char *built_in_commands[] = {
		"cd",
		"exit",
		"setenv",
		"unsetenv",
		"help"
	};

	void (*built_in_funcs[])(okeoma *oki) = {
		&cd_command,
		&exit_command,
		&setenv_command,
		&unsetenv_command,
		&help_command
	};
	int num_built_in_com = sizeof(built_in_commands) / sizeof(char *), i;

	for (i = 0; i < num_built_in_com; i++)
	{
		if (strcmp(oki->av[0], built_in_commands[i]) == 0)
		{
			(*built_in_funcs[i])(oki);
			return (0); /* Command executed */
		}
	}
	return (1); /* Not a built-in command */
}