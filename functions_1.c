#include "main.h"

/**
 * f_tokenizer - the initializer for string tokenization
 * @tokenizer: struct for storing the tokens
 * @input_string: string to tokenize
 *
 * Return: void
*/
void f_tokenizer(Tokenizer *tokenizer, char *input_string)
{
	tokenizer->cur_tok_st = input_string;
	tokenizer->nxt_tok_st = input_string;
}

/**
 * s_tok - function for tokenizing strings
 * @tokenizer: struct where token are stored
 * @delimiters: the delimeters for the tokenization
 *
 * Return: pointer to token
 * error: NULL if no more tokens are found
*/
char *s_tok(Tokenizer *tokenizer, const char *delimiters)
{
	char *token;

	if (tokenizer->cur_tok_st == NULL)
		return (NULL);
	/* Skip leading delimiters */
	tokenizer->cur_tok_st += strspn(tokenizer->cur_tok_st, delimiters);
	/* Check if end of string is reached */
	if (*tokenizer->cur_tok_st == '\0')
	{
		tokenizer->cur_tok_st = NULL;
		return (NULL);
	}
	tokenizer->nxt_tok_st = tokenizer->cur_tok_st;
	/* Find the end of the current token */
	tokenizer->nxt_tok_st += strcspn(tokenizer->nxt_tok_st, delimiters);
	if (*tokenizer->nxt_tok_st != '\0')
	{
		*tokenizer->nxt_tok_st = '\0';
		tokenizer->nxt_tok_st++;
	}
	else
	{
		tokenizer->nxt_tok_st = NULL;
	}
	token = tokenizer->cur_tok_st;
	tokenizer->cur_tok_st = tokenizer->nxt_tok_st;

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
	f_tokenizer(&oki->baxi, path_copy);
	token = s_tok(&oki->baxi, ":");
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
		token = s_tok(&oki->baxi, ":");
	}
	free(path_copy);
	return (NULL);
}

char *find_directory(const char *directory_name, okeoma *oki)
{
    char *path_env, *path_copy, *token, *dir_path;
    size_t token_len, dir_name_len;

    path_env = getenv("PATH");
    path_copy = strdup(path_env);
    f_tokenizer(&oki->baxi, path_copy);
    token = s_tok(&oki->baxi, ":");
    while (token)
    {
        token_len = strlen(token);
        dir_name_len = strlen(directory_name);
        dir_path = (char *)malloc((token_len + dir_name_len + 2) * sizeof(char));
        if (dir_path == NULL)
        {
            perror("Memory allocation failed");
            free(path_copy);
            return NULL;
        }
        strcpy(dir_path, token);
        strcat(dir_path, "/");
        strcat(dir_path, directory_name);
        if (access(dir_path, F_OK) == 0)
        {
            free(path_copy);
            return dir_path;
        }
        free(dir_path);
        token = s_tok(&oki->baxi, ":");
    }
    free(path_copy);
    return NULL;
}

void interactive(okeoma *oki)
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
		"getenv"
	};

	void (*built_in_funcs[])(okeoma *oki) = {
		&cd_command,
		&exit_command,
		&setenv_command,
		&unsetenv_command,
		&get_env_command
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
