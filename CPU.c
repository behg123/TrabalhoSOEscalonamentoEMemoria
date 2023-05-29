#include <stdio.h>
#include "CPU.h"

void run(Task *task, int slice)
{
    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
}
