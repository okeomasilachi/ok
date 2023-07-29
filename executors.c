#include "main.h"

/**
 * execute_builtin_command - this function runs built-in
 * @av: argument varable
 * @argv: argument variable
 * @command_count: current argument number
 * @command: arguments
 * @colon: for the command separator
 *
 * Return: 0 on success
 * error: 1 on error
*/
int execute_builtin_command(char **av, char **argv, size_t command_count,
char *command, char **colon)
{
	char *built_in_commands[] = {
		"cd",
		"exit"
	};

	void (*built_in_funcs[])(char **, char **, size_t, char *, char **) = {
		&cd_command,
		&exit_command,
	};
	int num_built_in_com = sizeof(built_in_commands) / sizeof(char *), i;

	for (i = 0; i < num_built_in_com; i++)
	{
		if (strcmp(av[0], built_in_commands[i]) == 0)
		{
			(*built_in_funcs[i])(av, argv, command_count, command, colon);
			return (0);
		}
	}
	return (1);
}


/**
 * find_executable - find the path to an execuitable file
 * @av: argument vector
 *
 * Return: the full path to the executable if it exists within the path
*/
char *find_executable(char **av)
{
	char *path_env, *path_copy, *token, *exe_path;
	size_t token_len, exec_name_len;

	if (access(av[0], X_OK) == 0)
	{
		exe_path = av[0];
		return (exe_path);
	}
	path_env = getenv("PATH");
	path_copy = strdup(path_env);
	token = string(path_copy, ":");
	while (token)
	{
		token_len = strlen(token);
		exec_name_len = strlen(av[0]);
		exe_path = (char *)malloc((token_len + exec_name_len + 2) * sizeof(char));
		if (exe_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		strcpy(exe_path, token);
		strcat(exe_path, "/");
		strcat(exe_path, av[0]);
		if (access(exe_path, X_OK) == 0)
		{
			free(path_copy);
			return (exe_path);
		}
		free(exe_path);
		token = string(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - create a process to execute executables
 * @av: argument varable
 * @argv: argument variable
 * @command_count: current argument number
 * @status: status of the last exited program
 * @st: file stream check
 *
 * Return: the status of the last executed program
*/
int execute_command(char **av, char **argv, int status,
size_t command_count, char st)
{
	char *ec;
	pid_t child_pid;

	ec = find_executable(av);
	if (ec == NULL)
	{
		print(STE, "%s: %d: %s: not found\n", argv[0], command_count, av[0]);
		if (st)
			exit(127);
	}
	if (ec != NULL)
	{
		child_pid = fork();
		if (child_pid == -1)
			perror("fork");
		else if (child_pid == 0)
		{
			execve(ec, av, environ);
			print(STE, "%s: %d: %s: Permission denied\n",
			argv[0], command_count, av[0]);
			return (EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
			free(ec);
			if (WIFEXITED(status))
				return (WEXITSTATUS(status));
		}
	}
	return (-1);
}

/**
 * exec - main execution function
 * @command:getline buffer
 * @av: argument vectors
 * @argv: argument vectors
 * @command_count: command execution number
 * @st: file stream check
 * @status: exit status of the last exited program
 * @colon: command separator
 *
 * Return: status of last executed program
*/
int exec(char *command, char **av, char **argv,
size_t command_count, char st, int status, char **colon)
{
	int i = 0;

	colon = split_vector(command, ";\n\t");
	for (i = 0; colon[i] != NULL; i++)
	{
		av = split_vector(colon[i], " \t\n\r");
		status = execute_builtin_command(av, argv, command_count, command, colon);
		if (status != 0)
			status = execute_command(av, argv, status, command_count, st);
	}
	if (isatty(STDIN_FILENO))
		arg_free(av, colon);
	return (status);
}
