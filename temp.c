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
    
    clearScreen();
    do 
    {
            printMenu();
            int task = selectTask(task);
            clearScreen();
            
            switch (task)
            {    
                case 1: 
                        addTask(listName, lineCounter(listName));
                        clearScreen();
                        break;
                case 2: 
                        deleteTask(listName);
                        clearScreen();
                        break;
                case 3: markTaskDone(listName);
                        break;
                case 4:         
                        printTasks(listName);
                        break;
                case 5: 
                        exit = 1;
                        break;
                default: printf("Invalid option.\n");
        }
     
    } while (!exit);

    return (0);
}