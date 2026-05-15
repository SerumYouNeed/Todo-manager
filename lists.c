#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tasks.h"

void addList(void)
{
    printf("Enter the name of the new list: \n");
    char listName[101];
    scanf(" %100s", listName);
    strcat(listName, ".txt");

    FILE *fp;
    fp = fopen(listName, "w");
    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return;
    }
    fclose(fp);

    FILE *listsFile;
    listsFile = fopen("lists.txt", "a");
    if (listsFile == NULL)
    {
        printf("Error opening file.\n");
        return; 
    }

    int listNumber = lineCounter("lists.txt");

    char buffer[101];
    while (fgets(buffer, sizeof buffer, listsFile) != NULL) 
    {
        if (strcmp(listName, buffer) == 0)
        {
            printf("List already exists.\n");
            fclose(listsFile);
            return;
        }
    }
    fprintf(listsFile, "%d. %s\n", listNumber, listName);
    fclose(listsFile);
}

void deleteList(void)
{
char listName[101];

    printf("Enter the name of the list to delete:\n");
    fgets(listName, sizeof listName, stdin);
    listName[strcspn(listName, "\n")] = '\0';

    FILE *listsFile = fopen("lists.txt", "r");
    if (listsFile == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempListsFile = fopen("temp_lists.txt", "w");
    if (tempListsFile == NULL)
    {
        printf("Error opening file.\n");
        fclose(listsFile);
        return;
    }

    char buffer[101];
    int newLineNum = 1;

    while (fgets(buffer, sizeof buffer, listsFile) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *stripedListName = removeFrontDigits(buffer);

        if (strcmp(stripedListName, listName) == 0)
        {
            continue;
        }

        fprintf(tempListsFile, "%d. %s\n", newLineNum++, stripedListName);
    }

    fclose(listsFile);
    fclose(tempListsFile);

    remove("lists.txt");
    rename("temp_lists.txt", "lists.txt");
}

void printLists(void)
{
    FILE *fp;
    fp = fopen("lists.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    printf("\n********************\n");
    printf("*    Your lists    *\n");
    printf("********************\n");
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        int position = 0;
        while (buffer[position] != '\0') 
        {
            if (buffer[position] == '.' && buffer[position + 1] == 't' && buffer[position + 2] == 'x' && buffer[position + 3] == 't') 
            {
                buffer[position] = '\0';
                break;
            }
            position++;
        }
        printf("%s\n", buffer);
    }
    printf("\n\n");
    fclose(fp);
}


void switchList(char *list, size_t size)
{
    printLists();

    printf("Enter the number or name of the list to switch to:\n");

    fgets(list, size, stdin);

    list[strcspn(list, "\n")] = '\0';
}