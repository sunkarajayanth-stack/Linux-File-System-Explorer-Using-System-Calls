#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#include "file_operations.h"

#define BUFFER_SIZE 4096
#define PATH_SIZE 1024

static void remove_newline(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

/* Display file information */

void file_information(void)
{
    char filename[PATH_SIZE];
    struct stat file_stat;

    printf("\nEnter file/directory name: ");

    fgets(filename, sizeof(filename), stdin);
    remove_newline(filename);

    if (stat(filename, &file_stat) == -1)
    {
        perror("stat");
        return;
    }

    printf("\n========================================\n");
    printf("           FILE INFORMATION\n");
    printf("========================================\n");

    printf("Name          : %s\n", filename);
    printf("Size          : %ld bytes\n", file_stat.st_size);
    printf("Inode         : %ld\n", file_stat.st_ino);
    printf("User ID       : %d\n", file_stat.st_uid);
    printf("Group ID      : %d\n", file_stat.st_gid);

    if (S_ISREG(file_stat.st_mode))
    {
        printf("Type          : Regular File\n");
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        printf("Type          : Directory\n");
    }
    else if (S_ISLNK(file_stat.st_mode))
    {
        printf("Type          : Symbolic Link\n");
    }
    else
    {
        printf("Type          : Other\n");
    }

    printf("Permissions   : ");

    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");

    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");

    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");

    printf("\n");

    printf("Last Modified : %s", ctime(&file_stat.st_mtime));
}

/* Read file using open, read and close */

void read_file(void)
{
    char filename[PATH_SIZE];
    char buffer[BUFFER_SIZE];

    printf("\nEnter file name: ");

    fgets(filename, sizeof(filename), stdin);
    remove_newline(filename);

    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return;
    }

    printf("\n========================================\n");
    printf("             FILE CONTENTS\n");
    printf("========================================\n");

    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(STDOUT_FILENO, buffer, bytes_read) == -1)
        {
            perror("write");
            break;
        }
    }

    if (bytes_read == -1)
    {
        perror("read");
    }

    printf("\n");

    close(fd);
}

/* Create file */

void create_file(void)
{
    char filename[PATH_SIZE];

    printf("\nEnter new file name: ");

    fgets(filename, sizeof(filename), stdin);
    remove_newline(filename);

    int fd = open(
        filename,
        O_CREAT | O_WRONLY | O_EXCL,
        0644
    );

    if (fd == -1)
    {
        perror("open");
        return;
    }

    close(fd);

    printf("File created successfully.\n");
}

/* Delete file */

void delete_file(void)
{
    char filename[PATH_SIZE];

    printf("\nEnter file name to delete: ");

    fgets(filename, sizeof(filename), stdin);
    remove_newline(filename);

    if (unlink(filename) == -1)
    {
        perror("unlink");
        return;
    }

    printf("File deleted successfully.\n");
}

/* Rename file or directory */

void rename_item(void)
{
    char oldname[PATH_SIZE];
    char newname[PATH_SIZE];

    printf("\nEnter current name: ");

    fgets(oldname, sizeof(oldname), stdin);
    remove_newline(oldname);

    printf("Enter new name: ");

    fgets(newname, sizeof(newname), stdin);
    remove_newline(newname);

    if (rename(oldname, newname) == -1)
    {
        perror("rename");
        return;
    }

    printf("Renamed successfully.\n");
}
