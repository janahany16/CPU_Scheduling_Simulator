#include <stdio.h>
#include "display.h"

void printGanttChart(const Timeline *timeline)
{
    int i;

    if (timeline == NULL || timeline->count == 0)
    {
        printf("Gantt Chart is empty.\n");
        return;
    }

    printf("\nGantt Chart:\n");

    for (i = 0; i < timeline->count; i++)
    {
        printf("%d | ", timeline->entries[i].startTime);

        if (timeline->entries[i].pid == IDLE_PID)
        {
            printf("IDLE | ");
        }
        else
        {
            printf("P%d | ", timeline->entries[i].pid);
        }
    }

    printf("%d\n", timeline->entries[timeline->count - 1].endTime);
}
