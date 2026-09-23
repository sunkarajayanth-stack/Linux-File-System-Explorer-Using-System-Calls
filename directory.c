#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <string.h>

#include "directory.h"

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

#define DT_REG 8
#define DT_DIR 4

static void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

/* List directory contents using getdents64 */

void list_directory(void)
{
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open(".", O_RDONLY | O_DIRECTORY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    int nread = syscall(SYS_getdents64, fd, buffer, BUFFER_SIZE);

    if (nread == -1)
    {
        perror("getdents64");
        close(fd);
        return;
    }

    printf("\n========================================\n");
    printf("          DIRECTORY CONTENTS\n");
    printf("========================================\n");

    int position = 0;

    while (position < nread)
    {
        struct linux_dirent64 *entry =
            (struct linux_dirent64 *)(buffer + position);

        if (entry->d_type == DT_DIR)
        {
            printf("[DIR ]  %s\n", entry->d_name);
        }
        else if (entry->d_type == DT_REG)
        {
            printf("[FILE]  %s\n", entry->d_name);
        }
        else
        {
            printf("[OTHER] %s\n", entry->d_name);
        }

        position += entry->d_reclen;
    }

    close(fd);
}

/* Change directory */

void change_directory(void)
{
    char path[PATH_SIZE];

    printf("\nEnter directory path: ");

    fgets(path, sizeof(path), stdin);
    remove_newline(path);

    if (chdir(path) == -1)
    {
        perror("chdir");
        return;
    }

    printf("Directory changed successfully.\n");
}

/* Go to parent directory */

void parent_directory(void)
{
    if (chdir("..") == -1)
    {
        perror("chdir");
        return;
    }

    printf("Moved to parent directory.\n");
}

/* Create directory */

void create_directory(void)
{
    char dirname[PATH_SIZE];

    printf("\nEnter new directory name: ");

    fgets(dirname, sizeof(dirname), stdin);
    remove_newline(dirname);

    if (mkdir(dirname, 0755) == -1)
    {
        perror("mkdir");
        return;
    }

    printf("Directory created successfully.\n");
}

/* Delete empty directory */

void delete_directory(void)
{
    char dirname[PATH_SIZE];

    printf("\nEnter directory name to delete: ");

    fgets(dirname, sizeof(dirname), stdin);
    remove_newline(dirname);

    if (rmdir(dirname) == -1)
    {
        perror("rmdir");
        return;
    }

    printf("Directory deleted successfully.\n");
}
