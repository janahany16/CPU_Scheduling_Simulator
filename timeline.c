#include <stdio.h>
#include "timeline.h"

void initializeTimeline(Timeline *timeline)
{
    timeline->count = 0;
}

int addTimelineEntry(Timeline *timeline, int startTime, int endTime, int pid)
{
    if (timeline == NULL)
    {
        return 0;
    }

    if (timeline->count >= MAX_TIMELINE_ENTRIES)
    {
        return 0;
    }

    if (endTime <= startTime)
    {
        return 0;
    }

    timeline->entries[timeline->count].startTime = startTime;
    timeline->entries[timeline->count].endTime = endTime;
    timeline->entries[timeline->count].pid = pid;

    timeline->count++;

    return 1;
}

void displayTimeline(const Timeline *timeline)
{
    int i;

    if (timeline == NULL || timeline->count == 0)
    {
        printf("Timeline is empty.\n");
        return;
    }

    printf("\nSimulation Timeline:\n");
    printf("-------------------------------\n");
    printf("Start\tEnd\tProcess\n");
    printf("-------------------------------\n");

    for (i = 0; i < timeline->count; i++)
    {
        printf("%d\t%d\t",
               timeline->entries[i].startTime,
               timeline->entries[i].endTime);

        if (timeline->entries[i].pid == IDLE_PID)
        {
            printf("IDLE\n");
        }
        else
        {
            printf("P%d\n", timeline->entries[i].pid);
        }
    }
}
