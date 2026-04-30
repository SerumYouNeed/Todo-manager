#include <stdio.h>
#include <string.h>

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
    FILE *fp;
    fp = fopen(s, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof buffer, fp) != NULL) 
    {
        printf("%s", buffer);
    }
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
            fprintf(tempFile, "%s", buffer);
        }
        currentTask++;
    }
    fclose(fp);
    fclose(tempFile);
    remove(s);
    rename("temp.txt", s);
}