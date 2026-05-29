#ifndef LISTS_H
#define LISTS_H

void addList(char* listName, size_t size);
void deleteList(void);
char* switchList(void);
void printLists(void);
int takeNumberFromLineAsString(char* line);
void promptUserForListName(char* list, size_t size);
int checkIfListExists(const char *listName);

#endif // LISTS_H   