#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <string.h>

#include "search.h"

#define BUFFER_SIZE 4096
#define PATH_SIZE 1024

struct linux_dirent64
{
    unsigned long long d_ino;
    long long d_off;
    unsigned short d_reclen;
    unsigned char d_type;
    char d_name[];
};

#define DT_DIR 4

static void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

static void search_directory(
    const char *directory,
    const char *target
)
{
    char buffer[BUFFER_SIZE];

    int fd = open(directory, O_RDONLY | O_DIRECTORY);

    if (fd == -1)
    {
        return;
    }

    int nread =
        syscall(SYS_getdents64, fd, buffer, BUFFER_SIZE);

    if (nread == -1)
    {
        close(fd);
        return;
    }

    int position = 0;

    while (position < nread)
    {
        struct linux_dirent64 *entry =
            (struct linux_dirent64 *)(buffer + position);

        if (strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
        {
            char fullpath[PATH_SIZE];

            snprintf(
                fullpath,
                sizeof(fullpath),
                "%s/%s",
                directory,
                entry->d_name
            );

            if (strcmp(entry->d_name, target) == 0)
            {
                printf("Found: %s\n", fullpath);
            }

            if (entry->d_type == DT_DIR)
            {
                search_directory(fullpath, target);
            }
        }

        position += entry->d_reclen;
    }

    close(fd);
}

void search(void)
{
    char filename[PATH_SIZE];

    printf("\nEnter file/directory name to search: ");

    fgets(filename, sizeof(filename), stdin);
    remove_newline(filename);

    printf("\nSearch Results:\n");
    printf("-------------------------\n");

    search_directory(".", filename);
}
