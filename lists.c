#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "tasks.h"

int checkIfListExists(const char *listName)
{
    strcat(listName, ".txt");
    
    FILE *fp;
    fp = fopen("lists.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[101];
    int exists = 0;
    long lineNumberfromBuffer;
    char lineNumberAsString[10];
    char *stripedListName;
    
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        lineNumberfromBuffer = strtol(buffer, &stripedListName, 10);
        snprintf(lineNumberAsString, sizeof lineNumberAsString, "%ld", lineNumberfromBuffer);
        stripedListName = formatListNameFromString(stripedListName);

        if (strcmp(listName, stripedListName) == 0 || strcmp(listName, lineNumberAsString) == 0)
        {
            exists = 1;
            break;
        }
    }
    fclose(fp);
    if (!exists)
    {
        printf("List does not exist.\n");
    }
    return exists;
}

void addList(void)
{
    printf("Enter the name of the new list: \n");
    char listName[101];
    fgets(listName, sizeof listName, stdin);
    listName[strcspn(listName, "\n")] = '\0';
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

    printf("Enter the name of the list or its number to delete: \n");
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
    long lineNumberfromBuffer;
    char lineNumberAsString[10];
    char *stripedListName;

    while (fgets(buffer, sizeof buffer, listsFile) != NULL)
    {   
        buffer[strcspn(buffer, "\n")] = '\0';

        lineNumberfromBuffer = strtol(buffer, &stripedListName, 10);
        snprintf(lineNumberAsString, sizeof lineNumberAsString, "%ld", lineNumberfromBuffer);
        stripedListName = formatListNameFromString(stripedListName);
 
        
        if (strcmp(stripedListName, listName) == 0 || strcmp(listName, lineNumberAsString) == 0)
        {
            printf("Are you sure you want to delete the list '%s'? (y/n): ", stripedListName);
            char confirmation[5];
            fgets(confirmation, sizeof confirmation, stdin);
            if (confirmation[0] == 'y' || confirmation[0] == 'Y')
            {   
                continue;
            }
            else
            {
                fprintf(tempListsFile, "%d. %s\n", newLineNum, strcat(stripedListName, ".txt"));
                newLineNum++;
                continue;
            }

        }

        fprintf(tempListsFile, "%d. %s\n", newLineNum, strcat(stripedListName, ".txt"));
        newLineNum++;
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
        char* listName;
        long position = strtol(buffer, &listName, 10);
        listName = formatListNameFromString(listName);
        printf("%ld. %s\n", position, listName);
        // printf("%s", buffer);
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