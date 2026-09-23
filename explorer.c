#include <stdio.h>
#include <unistd.h>
#include "explorer.h"

#define PATH_SIZE 1024

void show_current_directory(void)
{
    char cwd[PATH_SIZE];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return;
    }

    printf("Current Directory: %s\n", cwd);
}

void display_menu(void)
{
    printf("\n");
    printf("============================================\n");
    printf("       LINUX FILE SYSTEM EXPLORER\n");
    printf("============================================\n");

    show_current_directory();

    printf("\n");
    printf("1.  List Directory\n");
    printf("2.  Change Directory\n");
    printf("3.  Go to Parent Directory\n");
    printf("4.  File Information\n");
    printf("5.  Read File\n");
    printf("6.  Create File\n");
    printf("7.  Create Directory\n");
    printf("8.  Delete File\n");
    printf("9.  Delete Directory\n");
    printf("10. Rename File/Directory\n");
    printf("11. Search File\n");
    printf("12. Exit\n");

    printf("\nEnter choice: ");
}
