#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tasks.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <list_name>\n", argv[0]);
        return 1;
    }

    char listName[101];
    strcpy(listName, argv[1]);
    strcat(listName, ".txt");

    int exit = 0;
    
    do 
    {
        clearScreen();
        printMenu();
        int task = selectTask(task);
      
        switch (task)
        {    
                case 1: addTask(listName, lineCounter(listName));
                        break;
                case 2: deleteTask(listName);
                        break;
                case 3: // markComplete(listName);
                        break;
                case 4: printTasks(listName);
                        break;
                case 5: exit = 1;
                        break;
                default: printf("Invalid option.\n");
        }
     
    } while (!exit);

    return (0);
}