#include <stdio.h>
#include <unistd.h>


void cd(char **args)
{
    if (args[1] == NULL)
    {
        printf("cd: missing path\n");
        return;
    }

    if (chdir(args[1]) == -1)
    {
        perror("cd");
    }
}