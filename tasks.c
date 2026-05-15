#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// \033 or \x1b as escape ISO standard
// [H - home, [J - clear
void clearScreen()
{
   const char *CLEAR_SCREEN_ANSI = "\x1b[H\x1b[J";
   write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 7);
}

void addTask(char *s, int taskCounter)
{
    FILE *fp;
    fp = fopen(s, "a+");
    if (fp)
    {
        printf("Enter new task: \n");
        char task[1024];
        getchar(); // Consume the newline character left by scanf
        fgets(task, 1022, stdin);
        fprintf(fp, "%d. %s", taskCounter, task);
        fclose(fp);
    }
    else
    {
        printf("Error opening file.\n");
    }
}

char* removeFrontDigits(char* str)
{
    while (*str && isdigit(*str))
    {
        str++;
    }

    if (*str == '.')
        str++;

    if (*str == ' ')
        str++;

    return str;
}

int lineCounter(char *s)
{
    int linecount = 1;
    char buffer[1024];
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        return 1; // If the file doesn't exist, start with 1
    }
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        linecount++;
    }
    fclose(fp);
    return linecount;
}

void printTasks(char *s)
{
    clearScreen();
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    printf("********************\n");
    printf("%s\n", s);
    printf("********************\n");
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        printf("%s", buffer);
    }
    printf("\n\n");
    fclose(fp);
}

void updateTasksNumbers(char* file, int taskNum, char* markedTask, size_t markedTaskSize)
{
    FILE *tempFile;
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(tempFile);
        return; 
    }

    FILE *fp;
    fp = fopen(file, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        fclose(tempFile);
        return;
    }
    
    char buffer[1024];
    int currentTask = 1;
    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        if (buffer[0] == 'D' && buffer[1] == 'O' && buffer[2] == 'N' && buffer[3] == 'E')
        {
            // This line is marked as done, write it to tempFile without changing the task number
            fprintf(tempFile, "%s", buffer);  
            continue; 
        }
        if (currentTask == taskNum)
        {
            currentTask++;  
            strncpy(markedTask, removeFrontDigits(buffer), markedTaskSize);
            // snprintf(markedTask, sizeof markedTask, "%s", buffer);
            continue; 
        }
        if (currentTask > taskNum)
        {
            // Update the task number for tasks after the deleted one
            char *dotPos = strchr(buffer, '.');
            if (dotPos != NULL)
            {
                int newTaskNum = currentTask - 1;
                char newBuffer[1024];
                snprintf(newBuffer, sizeof newBuffer, "%d.%s", newTaskNum, dotPos + 1);
                fprintf(tempFile, "%s", newBuffer);
            }
        }
        else
        {
            fprintf(tempFile, "%s", buffer);
        }
        
        currentTask++;
    }
    remove(file);
    rename("temp.txt", file);
    fclose(tempFile);
    fclose(fp);
}

void markTaskDone(char *s)
{
    FILE *fp;
    fp = fopen(s, "a");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        fclose(fp);
        return;
    }
    printf("Enter the number of the task to mark as done: \n");
    int taskNum;
    scanf(" %d", &taskNum);

    char doneBuffer[1018];
    char done[1024];
    updateTasksNumbers(s, taskNum, doneBuffer, sizeof doneBuffer);
    snprintf(done, sizeof done, "DONE: %s", doneBuffer);
    fprintf(fp, "%s", doneBuffer);
    
    fclose(fp);
}


void deleteTask(char *s)
{
    printf("Enter the number of the task to delete: \n");
    int taskNum;
    scanf(" %d", &taskNum);

    updateTasksNumbers(s, taskNum, NULL, 0);
}