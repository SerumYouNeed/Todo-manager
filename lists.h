#ifndef LISTS_H
#define LISTS_H

int addList(char* listName);
void deleteList(char* listName);
char* switchList(void);
void printLists(void);
int takeNumberFromLineAsString(char* line);
void promptUserForListName(char* list, size_t size);
int checkIfListExists(const char *listName);

#endif // LISTS_H   