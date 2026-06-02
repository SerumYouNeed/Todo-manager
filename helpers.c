#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include <unistd.h>

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

void promptUserForTodo(char *todo, size_t size)
{
    printf("Enter the todo:\n");

    if (fgets(todo, size, stdin) != NULL)
    {
        todo[strcspn(todo, "\n")] = '\0';
    }
}

int lineCounter(char *s)
{
    int linecount = 1;
    char buffer[1024];
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        return 1; // If the file doesn't exist, start with 1
    }
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        linecount++;
    }
    fclose(fp);
    return linecount;
}

// \033 or \x1b as escape ISO standard
// [H - home, [J - clear
void clearScreen()
{
   const char *CLEAR_SCREEN_ANSI = "\x1b[H\x1b[J";
   write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 7);
}