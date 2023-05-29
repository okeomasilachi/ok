#include "main.h"

int main(int argc, char **argv)
{
	okeoma *oki = malloc(sizeof(okeoma));
	_in(oki, argv);
	(void)argc;
	(void)argv;
	
	if (oki->it)
		interactive(oki);
	else
	{
		non_interactive(oki);
		free(oki);
	}
	return 0;
}
