#ifndef METRICS_H
#define METRICS_H

#include "timeline.h"

typedef struct
{
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
} Metrics;

void calculateProcessMetrics(
    int arrivalTime,
    int burstTime,
    int pid,
    const Timeline *timeline,
    Metrics *metrics
);

void calculateAverageMetrics(
    Metrics metrics[],
    int count,
    double *averageTAT,
    double *averageWT,
    double *averageRT
);

void printMetrics(
    int pid,
    const Metrics *metrics
);

void printAverageMetrics(
    double averageTAT,
    double averageWT,
    double averageRT
);

#endif
