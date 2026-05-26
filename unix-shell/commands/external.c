#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "external.h"

void run_external(char **args)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);

        perror("execvp");
        _exit(1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
}