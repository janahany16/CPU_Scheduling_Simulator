#include <stdio.h>
#include "metrics.h"

void calculateProcessMetrics(
    int arrivalTime,
    int burstTime,
    int pid,
    const Timeline *timeline,
    Metrics *metrics
)
{
    int i;
    int firstStartTime = -1;
    int completionTime = -1;

    if (timeline == NULL || metrics == NULL)
    {
        return;
    }

    /* Search the Timeline */
    for (i = 0; i < timeline->count; i++)
    {
        if (timeline->entries[i].pid == pid)
        {
            /* First CPU execution */
            if (firstStartTime == -1)
            {
                firstStartTime = timeline->entries[i].startTime;
            }

            /* Last execution end = Completion Time */
            completionTime = timeline->entries[i].endTime;
        }
    }

    /* Process was not found in the Timeline */
    if (firstStartTime == -1 || completionTime == -1)
    {
        return;
    }

    /* CT = Completion Time */
    metrics->completionTime = completionTime;

    /* TAT = CT - AT */
    metrics->turnaroundTime =
        completionTime - arrivalTime;

    /* WT = TAT - BT */
    metrics->waitingTime =
        metrics->turnaroundTime - burstTime;

    /* RT = First CPU Start Time - AT */
    metrics->responseTime =
        firstStartTime - arrivalTime;
}


void calculateAverageMetrics(
    Metrics metrics[],
    int count,
    double *averageTAT,
    double *averageWT,
    double *averageRT
)
{
    int i;

    double totalTAT = 0;
    double totalWT = 0;
    double totalRT = 0;

    if (metrics == NULL || count <= 0 ||
        averageTAT == NULL ||
        averageWT == NULL ||
        averageRT == NULL)
    {
        return;
    }

    for (i = 0; i < count; i++)
    {
        totalTAT += metrics[i].turnaroundTime;
        totalWT += metrics[i].waitingTime;
        totalRT += metrics[i].responseTime;
    }

    *averageTAT = totalTAT / count;
    *averageWT = totalWT / count;
    *averageRT = totalRT / count;
}


void printMetrics(
    int pid,
    const Metrics *metrics
)
{
    if (metrics == NULL)
    {
        return;
    }

    printf(
        "P%d\tCT=%d\tTAT=%d\tWT=%d\tRT=%d\n",
        pid,
        metrics->completionTime,
        metrics->turnaroundTime,
        metrics->waitingTime,
        metrics->responseTime
    );
}


void printAverageMetrics(
    double averageTAT,
    double averageWT,
    double averageRT
)
{
    printf("\nAverage Turnaround Time: %.2f\n", averageTAT);
    printf("Average Waiting Time: %.2f\n", averageWT);
    printf("Average Response Time: %.2f\n", averageRT);
}
