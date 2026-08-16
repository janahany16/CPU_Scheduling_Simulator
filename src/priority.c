#include <stdlib.h>
#include "scheduler.h"

static int hasHigherPriority(const Process *a, const Process *b)
{
    if (a->priority != b->priority) return a->priority < b->priority;
    if (a->arrival_time != b->arrival_time) return a->arrival_time < b->arrival_time;
    return a->pid < b->pid;
}

static int findBestReadyProcess(const Process processes[], size_t count, int current_time)
{
    int best = -1;
    for (size_t i = 0; i < count; i++) {
        if (processes[i].completed || processes[i].arrival_time > current_time || processes[i].remaining_time <= 0)
            continue;

        if (best == -1 || hasHigherPriority(&processes[i], &processes[best]))
            best = (int)i;
    }
    return best;
}

int priority_schedule(const Process processes[], size_t count, Timeline *timeline)
{
    if (processes == NULL || timeline == NULL || count == 0) return 0;

    Process *work = malloc(count * sizeof(*work));
    if (work == NULL) return 0;

    for (size_t i = 0; i < count; ++i) {
        work[i] = processes[i];
        process_reset_runtime(&work[i]);
    }

    size_t completed_count = 0;
    int time = 0;

    while (completed_count < count) {
        int idx = findBestReadyProcess(work, count, time);

        if (idx == -1) {
            int next_arrival = -1;
            for (size_t i = 0; i < count; ++i) {
                if (!work[i].completed && work[i].arrival_time > time &&
                    (next_arrival == -1 || work[i].arrival_time < next_arrival)) {
                    next_arrival = work[i].arrival_time;
                }
            }
            if (next_arrival == -1) { free(work); return 0; }
            if (!timeline_add(timeline, time, next_arrival, TIMELINE_IDLE_PID)) { free(work); return 0; }
            time = next_arrival;
            continue;
        }

        if (!work[idx].started) {
            work[idx].started = 1;
            work[idx].first_start_time = time;
        }

        if (!timeline_add(timeline, time, time + 1, work[idx].pid)) { free(work); return 0; }

        --work[idx].remaining_time;
        ++time;

        if (work[idx].remaining_time == 0) {
            work[idx].completed = 1;
            work[idx].completion_time = time;
            work[idx].turnaround_time = time - work[idx].arrival_time;
            work[idx].waiting_time = work[idx].turnaround_time - work[idx].burst_time;
            work[idx].response_time = work[idx].first_start_time - work[idx].arrival_time;
            ++completed_count;
        }
    }
    free(work);
    return 1;
}