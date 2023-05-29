#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "schedule_rr_p.c"

#define SIZE 100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen("rr-schedule_pri.txt", "r");

    while (fgets(task, SIZE, in) != NULL)
    {
        char *temp;
        temp = strtok(task, ",");
        name = strdup(temp); // Faz uma c�pia da string usando strdup
        temp = strtok(NULL, ",");
        priority = atoi(temp);
        temp = strtok(NULL, ",");
        burst = atoi(temp);

        add(name, priority, burst);
    }

    fclose(in);

    schedule();

    return 0;
}
