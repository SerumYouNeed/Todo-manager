#ifndef TASKS_H
#define TASKS_H

void addTask(char *s);
int lineCounter(char *s);
void printTasks(char *s);
void clearScreen();
void markTaskDone(char *s);
void updateTasksNumbers(char* s, int taskNum);

#endif // TASKS_H