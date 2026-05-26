#include <stdio.h>

void echo(char **args, int i)
{
     int c = 1;
            while (c != i)
            {
                printf("%s ", args[c]);
                c++;
            }
            printf("\n");
}