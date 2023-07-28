#include "main.h"

/**
 * get_cwd - get the current directory of the calling process
 *
 * Return: the abolute path of the directory
*/
char *get_cwd(void)
{
	char path[MAX_PATH];
	char *pth = getcwd(path, sizeof(path));

	if (pth == NULL)
	{
		free(pth);
		return (NULL);
	}
	else
		return (pth);
}

