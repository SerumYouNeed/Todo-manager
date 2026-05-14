#ifndef TASKS_H
#define TASKS_H

void addTask(char *s, int taskCounter);
int lineCounter(char *s);
void printTasks(char *s);
void deleteTask(char *s);
void clearScreen();
char* removeFrontDigits(char* str);
void markTaskDone(char *s);

#endif // TASKS_H