#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tasks.h"
#include "lists.h"

// TODO: Implement error handling for file operations in the markTaskDone and deleteTask functions. Currently, if there is an error opening the files, the program simply prints an error message and continues execution. It would be better to handle these errors more gracefully, such as by exiting the function early or providing feedback to the user about the failure.
// TODO: Consider adding functionality to allow users to mark tasks as not done or to edit existing tasks. This would enhance the usability of the task manager and provide more flexibility for users to manage their tasks effectively../


int main(void)
{   
    char listName[101] = {0};
    int exit = 0;
    
    clearScreen();
    do 
    {
            printListsMenu();
            int task = selectTask();
            
            switch (task)
            {    
                case 1: 
                        addList();
                        clearScreen();
                        break;
                case 2: 
                        deleteList();
                        clearScreen();
                        break;
                case 3: 
                        switchList(listName, sizeof(listName));
                        clearScreen();
                        int previousMenu = 0;
                        do
                        {
                                printMenu(); 
                                int task = selectTask();
                                switch (task)
                                {
                                        case 1: int lineNum = lineCounter(listName);
                                                addTask(listName, lineNum);
                                                clearScreen();
                                                break;
                                        case 2: deleteTask(listName);
                                                clearScreen();
                                                break;
                                        case 3: markTaskDone(listName);
                                                clearScreen();
                                                break;
                                        case 4: printTasks(listName);
                                                break;
                                        case 5: previousMenu = 1;
                                                break;
                                        default: printf("Invalid option.\n");
                                }
                        } while (!previousMenu);
                        break;
                case 4:         
                        printLists();
                        break;
                case 5: 
                        exit = 1;
                        break;
                default: printf("Invalid option.\n");
        }
     
    } while (!exit);

    return (0);
}