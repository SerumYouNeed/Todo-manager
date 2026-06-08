#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tasks.h"
#include "lists.h"
#include "helpers.h"

// delete task

int main(void)
{   
    // listName format: "listName.txt"
    char listName[101];
    // todo format: "new todo" starts with letter, no longer than 100 characters
    char todo[101];
    int exit = 0;
    int task;
    clearScreen();

    do 
    {
        printListsMenu();
        task = selectTask();
            
        switch (task)
        {    
        case 1: 
                clearScreen();
                promptUserForListName(listName, sizeof listName);
                if (checkIfListExists(listName))
                {
                    printf("List already exists.\n");
                    break;
                }
                addList(listName);
                break;
        case 2: 
                clearScreen();
                promptUserForListName(listName, sizeof listName);
                if (!checkIfListExists(listName))
                {
                    printf("List does not exist.\n");
                    break;
                }
                deleteList(listName);
                break;
        case 3: 
                int previousMenu = 0;
                clearScreen();
                promptUserForListName(listName, sizeof listName);
                if (!checkIfListExists(listName))
                {
                        break;
                }
                do
                {
                        printMenu(); 
                        task = selectTask();
                        switch (task)
                        {
                                case 1:
                                        promptUserForTodo(todo, sizeof todo);
                                        addTask(listName, todo);
                                        clearScreen();
                                        break;
                                case 2: //deleteTask(listName);
                                        clearScreen();
                                        break;
                                case 3: markTaskDone(listName);
                                        clearScreen();
                                        break;
                                case 4: 
                                        clearScreen();
                                        printTasks(listName);
                                        break;
                                case 5: 
                                        previousMenu = 1;
                                        break;
                                default: printf("Invalid option.\n");
                        }
                } while (!previousMenu);
                break;
        case 4:     
                clearScreen();    
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