#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

void insert(struct node **head, Task *newTask)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->task = newTask;
    newNode->next = NULL;
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        struct node *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void delete(struct node **head, Task *task)
{
    struct node *temp;
    struct node *prev;
    temp = *head;
    if (strcmp(task->name, temp->task->name) == 0)
    {
        *head = (*head)->next;
        free(temp);
    }
    else
    {
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == NULL)
        {
            printf("Task not found in the list.\n");
            return;
        }
        prev->next = temp->next;
        free(temp);
    }
}

void traverse(struct node *head)
{
    struct node *temp = head;
    while (temp != NULL)
    {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}

void swap(struct node *a, struct node *b)
{
    Task *temp = a->task;
    a->task = b->task;
    b->task = temp;
}

void sortByPriority(struct node *head)
{
    struct node *i, *j;
    for (i = head; i != NULL; i = i->next)
    {
        struct node *minNode = i;
        for (j = i->next; j != NULL; j = j->next)
        {
            if (j->task->priority < minNode->task->priority)
            {
                minNode = j;
            }
        }
        swap(i, minNode);
    }
}
