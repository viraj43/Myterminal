#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include "../commands/pwd.h"

#define RESET  "\033[0m"
#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"

void info(void)
{
    uid_t uid = getuid();

    struct passwd *pw = getpwuid(uid);

    if (pw == NULL)
    {
        perror("getpwuid");
        return;
    }

    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1)
    {
        perror("gethostname");
        return;
    }

    printf(RED "%s@%s" RESET, pw->pw_name, hostname);

    printf(RESET ":");

    printf(YELLOW);
    pwd();
    printf(RESET);
}