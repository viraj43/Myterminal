#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <grp.h>

#include <sys/stat.h>
#include <pwd.h>
#include <time.h>

void ls(char **args)
{
    DIR *dir = opendir(".");
    struct dirent *entry;
    int showHidden = 0;
    int longFormat=0;

    if (args[1] != NULL && strcmp(args[1], "-a") == 0)
    {
        showHidden = 1;
    }
    if (args[1] != NULL && strcmp(args[1], "-l") == 0)
    {
        longFormat = 1;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name[0] == '.' && showHidden == 0)
            continue;
        else if (longFormat == 1 && entry->d_name[0] != '.')
        {
            struct stat file_info;
            if (stat(entry->d_name, &file_info) == -1)
            {
                perror("stat");
                continue;
            }
            if (S_ISDIR(file_info.st_mode))
                printf("d");
            else if (S_ISLNK(file_info.st_mode))
                printf("l");
            else
                printf("-");
            printf((file_info.st_mode & S_IRUSR) ? "r" : "-");
            printf((file_info.st_mode & S_IWUSR) ? "w" : "-");
            printf((file_info.st_mode & S_IXUSR) ? "x" : "-");

            printf((file_info.st_mode & S_IRGRP) ? "r" : "-");
            printf((file_info.st_mode & S_IWGRP) ? "w" : "-");
            printf((file_info.st_mode & S_IXGRP) ? "x" : "-");

            printf((file_info.st_mode & S_IROTH) ? "r" : "-");
            printf((file_info.st_mode & S_IWOTH) ? "w" : "-");
            printf((file_info.st_mode & S_IXOTH) ? "x" : "-");

            printf(" ");

            struct passwd *pw = getpwuid(file_info.st_uid);
            struct group *gr = getgrgid(file_info.st_gid);
            printf("%s %s ", pw->pw_name, gr->gr_name);

            char time_buf[100];
            struct tm *time_info = localtime(&file_info.st_mtime);

            strftime(time_buf,sizeof(time_buf),"%b %d %H:%M",time_info);
            printf("%ld ", file_info.st_size);
            printf("%s ",time_buf);


            printf("%s ", entry->d_name);

            printf("\n");
        }
        else
        {
            printf("%s ", entry->d_name);
        }
    }
    closedir(dir);
}