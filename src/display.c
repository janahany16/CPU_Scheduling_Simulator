#include <stdio.h>
#include "display.h"

void printGanttChart(const Timeline *timeline)
{
    if (timeline == NULL || timeline->count == 0)
    {
        printf("Gantt Chart is empty.\n");
        return;
    }

    printf("\nGantt Chart:\n");

    for (size_t i = 0; i < timeline->count; i++)
    {
        printf("%d | ", timeline->segments[i].start);

        if (timeline->segments[i].pid == TIMELINE_IDLE_PID)
        {
            printf("IDLE | ");
        }
        else
        {
            printf("P%d | ", timeline->segments[i].pid);
        }
    }
    printf("%d\n", timeline->segments[timeline->count - 1].end);
}