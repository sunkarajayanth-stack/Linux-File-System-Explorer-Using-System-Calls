#include <stdio.h>
#include <stdlib.h>

#include "explorer.h"
#include "directory.h"
#include "file_operations.h"
#include "search.h"

int main(void)
{
    char input[20];
    int choice;

    while (1)
    {
        display_menu();

        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice)
        {
            case 1:
                list_directory();
                break;

            case 2:
                change_directory();
                break;

            case 3:
                parent_directory();
                break;

            case 4:
                file_information();
                break;

            case 5:
                read_file();
                break;

            case 6:
                create_file();
                break;

            case 7:
                create_directory();
                break;

            case 8:
                delete_file();
                break;

            case 9:
                delete_directory();
                break;

            case 10:
                rename_item();
                break;

            case 11:
                search();
                break;

            case 12:
                printf("\nExiting Linux File System Explorer...\n");
                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }

    return 0;
}
