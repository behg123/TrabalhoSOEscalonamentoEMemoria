#ifndef SCHEDULE_RR_H_INCLUDED
#define SCHEDULE_RR_H_INCLUDED
#define MIN_PRIORITY 1
#define MAX_PRIORITY 10
#include "CPU.c"

void add(char *name, int priority, int burst);

void scheduleRR();


#endif // SCHEDULE_RR_H_INCLUDED
