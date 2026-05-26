#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>

#include "pwd.h"

void pwd(void)
{

    struct stat current_info;
    struct stat parent_info;
    if (stat(".", &current_info) == -1)
    {
        perror("stat");
    }

    if (stat("..", &parent_info) == -1)
    {
        perror("stat");
    }
    char *director[1000];
    int i = 0;

    int saved_dir = open(".", O_RDONLY);

    while (!(current_info.st_ino == parent_info.st_ino &&
             current_info.st_dev == parent_info.st_dev))
    {
        DIR *parent_dir = opendir("..");
        struct dirent *entry;
        while ((entry = readdir(parent_dir)) != NULL)
        {
            char path[1200];
            struct stat entry_info;
            snprintf(path, sizeof(path), "../%s", entry->d_name);
            if (stat(path, &entry_info) == -1)
            {
                continue;
            }
            if (entry_info.st_ino == current_info.st_ino &&
                entry_info.st_dev == current_info.st_dev)
            {
                director[i] = strdup(entry->d_name);
                i++;
                break;
            }
        }
        closedir(parent_dir);
        chdir("..");
        stat(".", &current_info);
        stat("..", &parent_info);
    }
    printf("/");
    for (int j = i - 1; j >= 0; j--)
    {
        if (j == 0)
        {
            printf("%s", director[j]);
        }
        else
        {
            printf("%s/", director[j]);
        }
    }
    fchdir(saved_dir);
    close(saved_dir);
}