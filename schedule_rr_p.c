#include "schedule_rr_p.h"
#include <locale.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

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
    sortByPriority(head);
    struct node *temp = head;
    QueryPerformanceFrequency(&frequency);
    LARGE_INTEGER startTime;
    QueryPerformanceCounter(&startTime);
    LARGE_INTEGER startRound;
    QueryPerformanceCounter(&startRound);

    while (temp != NULL)
    {
        int currentPriority = temp->task->priority;
        printf("============================================\n\n");

        while (temp != NULL && temp->task->priority == currentPriority)
        {
            run(temp->task, QUANTUM);

            if (temp->task->burst == 0)
            {
                char *nome = temp->task->name;
                struct node *nextNode = temp->next;
                delete (&head, temp->task);
                printf("It took %.9f seconds to complete the program %s.\n\n", getTime(startTime), nome);
                if (nextNode != NULL)
                {
                    temp = nextNode;
                }
                else
                {
                    temp = head;
                    printf("--------------------------------------------\n");
                    printf("\nIt took %.9f seconds to complete the round.\n\n", getTime(startRound));
                    printf("\nIt took %.9f seconds since the beginning.\n\n", getTime(startTime));
                    printf("============================================\n\n");
                }
            }
            else
            {
                temp->task->burst -= QUANTUM;

                if (temp->next != NULL && temp->next->task->priority == currentPriority)
                {
                    temp = temp->next;
                }
                else
                {
                    temp = head;
                    printf("--------------------------------------------\n");
                    printf("\nIt took %.9f seconds to complete the round.\n\n", getTime(startRound));
                    printf("\nIt took %.9f seconds since the beginning.\n\n", getTime(startTime));
                    printf("============================================\n\n");
                    QueryPerformanceCounter(&startRound);
                }
            }
        }

        if (temp != NULL)
        {
            currentPriority = temp->task->priority;
        }
    }

    printf("--------------------------------------------\n");
    printf("\nIt took %.9f seconds to complete all the programs.\n\n", getTime(startTime));
    printf("============================================\n");
}
