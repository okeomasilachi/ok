#include "main.h"

int main(int argc, char **argv)
{
	okeoma *info = malloc(sizeof(okeoma));
	_in(info, argv);
	(void)argc;
	(void)argv;
	
	if (info->it)
		interactive(info);
	else
	{
		non_interactive(info);
		free(info);
	}
	return 0;
}
