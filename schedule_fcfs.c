#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include "schedule_fcfs.h"

struct node *head = NULL;
LARGE_INTEGER frequency;

double getTime(LARGE_INTEGER startTime)
{
    LARGE_INTEGER endTime;
    QueryPerformanceCounter(&endTime);
    double executionTotal = (double)(endTime.QuadPart - startTime.QuadPart) / (double)frequency.QuadPart;

    return executionTotal;
}

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    insert(&head, task);
}

void schedule()
{
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER startRound;
    QueryPerformanceCounter(&startRound);

    while (head != NULL)
    {
        run(head->task, QUANTUM);
        head->task->burst -= QUANTUM;

        if (head->task->burst == 0)
        {
            delete (&head, head->task);
            printf("--------------------------------------------\n");
            printf("\nIt took %.9f seconds to complete the program.\n\n", getTime(startRound));
            printf("\nIt took %.9f seconds since the beginning.\n\n", getTime(startTime));
            printf("============================================\n\n");
            QueryPerformanceCounter(&startRound);
        }
    }

    printf("\nIt took %.9f seconds to complete all the programs.\n\n", getTime(startTime));
    printf("============================================\n");
}
