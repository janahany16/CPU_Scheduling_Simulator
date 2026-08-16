#include <stdio.h>
#include "metrics.h"

void calculateProcessMetrics(int arrivalTime, int burstTime, int pid, const Timeline *timeline, Metrics *metrics)
{
    int firstStartTime = -1;
    int completionTime = -1;

    if (timeline == NULL || metrics == NULL) return;

    for (size_t i = 0; i < timeline->count; i++)
    {
        if (timeline->segments[i].pid == pid)
        {
            if (firstStartTime == -1) firstStartTime = timeline->segments[i].start;
            completionTime = timeline->segments[i].end;
        }
    }

    if (firstStartTime == -1 || completionTime == -1) return;

    metrics->completionTime = completionTime;
    metrics->turnaroundTime = completionTime - arrivalTime;
    metrics->waitingTime = metrics->turnaroundTime - burstTime;
    metrics->responseTime = firstStartTime - arrivalTime;
}

void calculateAverageMetrics(Metrics metrics[], int count, double *averageTAT, double *averageWT, double *averageRT)
{
    double totalTAT = 0, totalWT = 0, totalRT = 0;
    if (metrics == NULL || count <= 0 || averageTAT == NULL || averageWT == NULL || averageRT == NULL) return;

    for (int i = 0; i < count; i++)
    {
        totalTAT += metrics[i].turnaroundTime;
        totalWT += metrics[i].waitingTime;
        totalRT += metrics[i].responseTime;
    }

    *averageTAT = totalTAT / count;
    *averageWT = totalWT / count;
    *averageRT = totalRT / count;
}

void printMetrics(int pid, const Metrics *metrics)
{
    if (metrics == NULL) return;
    printf("P%d\tCT=%d\tTAT=%d\tWT=%d\tRT=%d\n", pid, metrics->completionTime, metrics->turnaroundTime, metrics->waitingTime, metrics->responseTime);
}

void printAverageMetrics(double averageTAT, double averageWT, double averageRT)
{
    printf("\nAverage Turnaround Time: %.2f\n", averageTAT);
    printf("Average Waiting Time: %.2f\n", averageWT);
    printf("Average Response Time: %.2f\n", averageRT);
}