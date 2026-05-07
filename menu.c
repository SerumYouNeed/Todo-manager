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
    printf("5. Exit.\n");
}

int selectTask(int a)
{
    printf("********************\n");
    printf("Select a task:  ");
    scanf(" %d", &a);
    return a;
}