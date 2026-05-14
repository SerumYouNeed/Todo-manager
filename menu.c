#include <stdio.h>

void printMenu(void)
{
    printf("********************\n");
    printf("*      OPTIONS     *\n");
    printf("********************\n");
    printf("1. Add task.\n");
    printf("2. Delete task.\n");
    printf("3. Mark as complete.\n");
    printf("4. Print list.\n");
    printf("5. Unmark as complete.\n");
    printf("6. Exit.\n");
}

void printListsMenu(void)
{
    printf("********************\n");
    printf("*      OPTIONS     *\n");
    printf("********************\n");
    printf("1. Add new list.\n");
    printf("2. Delete list.\n");
    printf("3. Switch list.\n");
    printf("4. Print lists.\n");
    printf("5. Exit.\n");
}

int selectTask(int a)
{
    printf("********************\n");
    printf("Select a task:  ");
    scanf(" %d", &a);
    return a;
}

int selectList(int a)
{
    printf("********************\n");
    printf("Select a list:  ");
    scanf(" %d", &a);
    return a;
}