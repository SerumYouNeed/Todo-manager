#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "tasks.h"


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
    
    return exists;
}

/**
 * Add a new list
 *
 * If the list exists return 1, if the list is created successfully return 0, if there is an error creating the file return 1.
 */
int addList(char* listName, size_t size)
{
    FILE *fp;
    fp = fopen(listName, "w");
    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }
    fclose(fp);

    FILE *listsFile;
    listsFile = fopen("lists.txt", "a");
    if (listsFile == NULL)
    {
        printf("Error opening file.\n");
        return 1; 
    }

    int listNumber = lineCounter("lists.txt");

    
    if (checkIfListExists(listName))
        {
            printf("List already exists.\n");
            fclose(listsFile);
            return 1;
        }
    
    fprintf(listsFile, "%d. %s\n", listNumber, listName);
    fclose(listsFile);
    return 0;
}

/**
 * Delete a list
 *
 * If the list does not exist return 1, if the list is deleted successfully return 0, if there is an error opening the file return 1.
 */
int deleteList(char* listName, size_t size)
{
    FILE *listsFile = fopen("lists.txt", "r");
    if (listsFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    FILE *tempListsFile = fopen("temp_lists.txt", "w");
    if (tempListsFile == NULL)
    {
        printf("Error opening file.\n");
        fclose(listsFile);
        return 1;
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
    return 0;
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

int takeNumberFromLineAsString(char* line)
{
    long number = strtol(line, NULL, 10);
    return (int)number;
}

void promptUserForListName(char* list, size_t size) 
{
    printf("Enter the name or a number of the list: \n");
    if (fgets(list, size, stdin) != NULL) 
    {
        list[strcspn(list, "\n")] = '\0';
        strncat(list, ".txt", size - strlen(list) - 1);
    }
}