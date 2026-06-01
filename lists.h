#ifndef LISTS_H
#define LISTS_H

void addList(char* listName);
void deleteList(char* listName);
char* switchList(void);
void printLists(void);
int checkIfListExists(const char *listName);

#endif // LISTS_H   