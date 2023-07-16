#include "main.h"


int main(int ac, const char **av)
{
	char *fpath = NULL, *tok, *path = getenv("PATH");
	int len;
	(void)len;
	if (ac > 2 || ac < 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s Filename\n", av[0]);
		return (-1);
	}
	len = strlen(av[1]);
	tok = strtok(path, ":");
	while (tok)
	{
		fpath = malloc(sizeof(char) * (strlen(tok) + 2 + len));
		fpath[0] = '\0';
		strcpy(fpath, tok);
		strcat(fpath, "/");
		strcat(fpath, av[1]);
		if (access(fpath, F_OK) == 0)
		{
			printf("%s\n", fpath);
			return(0);
		}
		tok = strtok(NULL, ":");
	}
	printf("No such file\n");
	return (1);
}
