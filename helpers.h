#ifndef HELPERS_H
#define HELPERS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

char* stripFrontCharactersFromListName(char* listName);
int takeNumberFromLineAsString(char* line);
void promptUserForListName(char* list, size_t size);
char* formatListNameFromString(char* line);
void promptUserForTodo(char* todo, size_t size);
int lineCounter(char *s);
void clearScreen();

#endif // HELPERS_H