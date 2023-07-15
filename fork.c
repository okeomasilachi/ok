#include "shell.h"

pid_t f_5(void)
{
    int status = 0;
    char *arr[100] = {"/bin/ls", "-l", "/tmp"};

    pid_t pid = fork();
    if (pid == -1)
    {
        return (pid);
    }
    else if (pid == 0)
    {
        execve(arr[0], arr, NULL);
    }
    else
    {
        waitpid(pid, &status, 0);
        return (pid);
    }
}
int main(void)
{
    int i = 0;

    for (i; i < 5; i++)
    {
        pid_t pid;

        pid = f_5();
        printf("PID of %d process = %d\n", i, pid);
        printf("Parent process = %d\n", getppid());
    }
    return (0);

}