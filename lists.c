#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "tasks.h"
#include "helpers.h"


/**
 * Check if a list exists
 *
 * @param listName Name of the list to check
 * @return 1 if the list exists, 0 otherwise
 */
int checkIfListExists(const char *listName)
{
    FILE *fp;
    fp = fopen("lists.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
 
    }

    char buffer[101];
    int exists = 0;
    char *stripedListName;
    
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        
        stripedListName = stripFrontCharactersFromListName(buffer);

        if (strcmp(listName, stripedListName) == 0)
        {
            exists = 1;
            break;
        }
    }
    fclose(fp);
    
    return exists;
}

/**
 * Add a new list
 *
 * @param listName Name of the list to add in format "listName.txt"
 */
void addList(char* listName)
{
    FILE *fp;
    fp = fopen(listName, "w");
    if (fp == NULL)
    {
        printf("Error creating file.\n");
    }
    fclose(fp);

    FILE *listsFile;
    listsFile = fopen("lists.txt", "a");
    if (listsFile == NULL)
    {
        printf("Error opening file.\n");
    }

    int listNumber = lineCounter("lists.txt");

    fprintf(listsFile, "%d. %s\n", listNumber, listName);
    fclose(listsFile);
}

/**
 * Delete a list
 *
 * @param listName Name of the list to delete in format "listName.txt"
 */
void deleteList(char* listName)
{
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
    char *stripedListName;

    while (fgets(buffer, sizeof buffer, listsFile) != NULL)
    {   
        buffer[strcspn(buffer, "\n")] = '\0';

        stripedListName = stripFrontCharactersFromListName(buffer);

 
        
        if (strcmp(stripedListName, listName) == 0)
        {
            printf("Are you sure you want to delete the list '%s'? (y/n): ", formatListNameFromString(buffer));
            char confirmation[5];
            fgets(confirmation, sizeof confirmation, stdin);
            if (confirmation[0] == 'y' || confirmation[0] == 'Y')
            {   
                continue;
            }
            else
            {
                fprintf(tempListsFile, "%d. %s\n", newLineNum, stripedListName);
                newLineNum++;
                continue;
            }

        }

        fprintf(tempListsFile, "%d. %s\n", newLineNum, stripedListName);
        newLineNum++;
    }

    fclose(listsFile);
    fclose(tempListsFile);

    remove("lists.txt");
    rename("temp_lists.txt", "lists.txt");
    return;
}

/**
 * Print all lists
 *
 * Reads the lists.txt file and displays the names of all the lists to the user.
 */
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