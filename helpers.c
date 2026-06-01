#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

char* stripFrontCharactersFromListName(char* line)
{
    while (*line && isdigit(*line))
        line++;

    if (*line == '.')
        line++;

    if (*line == ' ')
        line++;

    char *start = line;

    char *dot = strstr(start, ".txt");
    char* end = dot + 4;
    *(end+1) = '\0';
    return start;
}

char* formatListNameFromString(char* line)
{
    while (*line && isdigit(*line))
        line++;
    
    if (*line == '.')
        line++;
    
    if (*line == ' ')
        line++;
    
    char *start = line;
    
    char *dot = strstr(start, ".txt");
    if (dot)
        *dot = '\0';

    return line;
}

int takeNumberFromLineAsString(char* line)
{
    long number = strtol(line, NULL, 10);
    return (int)number;
}

void promptUserForListName(char *list, size_t size)
{
    printf("Enter the name of the list:\n");

    if (fgets(list, size, stdin) != NULL)
    {
        list[strcspn(list, "\n")] = '\0';
        strncat(list, ".txt", size - strlen(list) - 1);
    }
}