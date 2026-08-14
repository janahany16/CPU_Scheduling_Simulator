#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

#define PROCESS_NOT_SET (-1)

typedef struct {
    /* Original input data: never modified by a scheduler. */
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    /* Runtime scheduling state: copied/reset for each simulation. */
    int remaining_time;
    int started;
    int completed;

    /* Scheduling statistics, filled after a simulation. */
    int first_start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

void process_init(Process *p, int pid, int arrival_time, int burst_time, int priority);
void process_reset_runtime(Process *p);
int process_validate(const Process *p);
int processes_have_unique_pids(const Process processes[], size_t count);

#endif
