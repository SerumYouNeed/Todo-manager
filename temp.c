#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tasks.h"


// TODO: Refactor the markTaskDone and deleteTask functions to avoid code duplication and improve readability. Consider creating a helper function that handles the common logic of reading tasks, updating task numbers, and writing to temporary files. This will make the code cleaner and easier to maintain.
// TODO: Implement error handling for file operations in the markTaskDone and deleteTask functions. Currently, if there is an error opening the files, the program simply prints an error message and continues execution. It would be better to handle these errors more gracefully, such as by exiting the function early or providing feedback to the user about the failure.
// TODO: Consider adding functionality to allow users to mark tasks as not done or to edit existing tasks. This would enhance the usability of the task manager and provide more flexibility for users to manage their tasks effectively.
// TODO: Implement a feature to allow user to create a new list, delete an existing one, or switch between different lists. This would make the task manager more versatile and allow users to organize their tasks into different categories or projects. 
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