#include <stdlib.h>
#include "scheduler.h"

static int compare_arrival_pid(const void *a, const void *b)
{
    const Process *x = (const Process *)a;
    const Process *y = (const Process *)b;

    if (x->arrival_time != y->arrival_time)
        return x->arrival_time < y->arrival_time ? -1 : 1;
    if (x->pid != y->pid)
        return x->pid < y->pid ? -1 : 1;
    return 0;
}

int fcfs_schedule(const Process processes[], size_t count, Timeline *timeline)
{
    if (processes == NULL || timeline == NULL || count == 0)
        return 0;

    /* Work on a private copy so the original workload remains unchanged. */
    Process *work = malloc(count * sizeof(*work));
    if (work == NULL)
        return 0;

    for (size_t i = 0; i < count; ++i) {
        work[i] = processes[i];
        process_reset_runtime(&work[i]);
    }

    qsort(work, count, sizeof(*work), compare_arrival_pid);

    int time = 0;

    for (size_t i = 0; i < count; ++i) {
        if (time < work[i].arrival_time) {
            if (!timeline_add(timeline, time, work[i].arrival_time,
                              TIMELINE_IDLE_PID)) {
                free(work);
                return 0;
            }
            time = work[i].arrival_time;
        }

        work[i].started = 1;
        work[i].first_start_time = time;

        if (!timeline_add(timeline, time, time + work[i].burst_time, work[i].pid)) {
            free(work);
            return 0;
        }

        time += work[i].burst_time;
        work[i].remaining_time = 0;
        work[i].completed = 1;
        work[i].completion_time = time;
        work[i].turnaround_time = time - work[i].arrival_time;
        work[i].waiting_time = work[i].turnaround_time - work[i].burst_time;
        work[i].response_time = work[i].first_start_time - work[i].arrival_time;
    }

    free(work);
    return 1;
}