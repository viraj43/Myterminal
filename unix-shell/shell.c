#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>

#include "./commands/pwd.h"
#include "./commands/echo.h"
#include "./commands/clear.h"
#include "./commands/ls.h"
#include "./commands/cd.h"
#include "./commands/external.h"
#include "./utils/info.h"

int main()
{

    while (1)
    {
        char line[1000];
        info();
        printf("$ ");
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "exit") == 0)
        {
            break;
        }

        char *token;
        char *args[1000];
        token = strtok(line, " ");
        int i = 0;
        while (token != NULL)
        {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        if (args[0] == NULL)
        {
            continue;
        }
        if (strcmp(args[0], "echo") == 0)
        {
            echo(args, i);
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            pwd();
            printf("\n");
        }
        else if (strcmp(args[0], "ls") == 0)
        {
            ls(args);
            printf("\n");
        }
        else if (strcmp(args[0], "clear") == 0)
        {
            clear();
            printf("\n");
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            cd(args);
            printf("\n");
        }
        else
        {
            run_external(args);
        }
    }
}