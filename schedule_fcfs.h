#ifndef SCHEDULE_FCFS_H_INCLUDED
#define SCHEDULE_FCFS_H_INCLUDED
#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#include "CPU.c"


// add a task to the list
void add(char *name, int priority, int burst);

// invoke the scheduler
void scheduleFCFS();

#endif // SCHEDULE_FCFS_H_INCLUDED
