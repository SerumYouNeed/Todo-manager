#include <stdio.h>
#include <string.h>
#include <unistd.h>

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

int lineCounter(char *s)
{
    int linecount = 1;
    char buffer[1024];
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        return 1; // If the file doesn't exist, we start with 1 task
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

void deleteTask(char *s)
{
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
    }
    printf("Enter the number of the task to delete: \n");
    int taskNum;
    scanf(" %d", &taskNum);

    FILE *tempFile;
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return; 
    }
    char buffer[1024];
    int currentTask = 1;
    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        if (currentTask != taskNum)
        {
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
                else
                {
                    fprintf(tempFile, "%s", buffer); // If no dot is found, write the line as is
                }
            }
            else
            {
                fprintf(tempFile, "%s", buffer);
            }
        }
        currentTask++;
    }
    fclose(fp);
    fclose(tempFile);
    remove(s);
    rename("temp.txt", s);
}

void markTaskDone(char *s)
{
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
    }
    printf("Enter the number of the task to mark as done: \n");
    int taskNum;
    scanf(" %d", &taskNum);

    FILE *tempFile;
    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return; 
    }
    char buffer[1024];
    int currentTask = 1;
    char doneLine[1024];
    while (fgets(buffer, sizeof buffer, fp) != NULL)
    {
        if (currentTask == taskNum)
        {
            // Mark the task as done by adding [DONE] at the beginning of the line
            snprintf(doneLine, sizeof doneLine, "[DONE] %s", buffer);
            continue;
        }
    
        fprintf(tempFile, "%s", buffer);
        currentTask++;
    }
    fprintf(tempFile, "%s", "*********************\n");
    fprintf(tempFile, "%s", doneLine);
    fclose(fp);
    fclose(tempFile);
    remove(s);
    rename("temp.txt", s);
}