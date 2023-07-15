#include "shell.h"


char *find(const char *str)
{
    char *path = getenv("PATH"), *f_path = NULL, *tok = NULL;

    tok = strtok(path, ":");


    while (tok)
    {
        f_path = malloc(sizeof(char) * (strlen(tok) + strlen(str) + 2));
        strcpy(f_path, tok);
        strcat(f_path, "/");
        strcat(f_path, str);

        /*printf("%s\n", f_path);*/
        if (access(f_path, F_OK) == 0)
        {
            return (f_path);
        }
        strtok(NULL, ":");
    }

    return (NULL);

}


int main(int ac, char *av[])
{
    char *vary = NULL;
    if (ac > 2)
    {
        dprintf(stderr, "Usage: _which filename\n");
    }

     vary = find(av[1]);

     




    
}