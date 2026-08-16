#include "process.h"

void process_init(Process *p, int pid, int arrival_time, int burst_time, int priority)
{
    if (p == NULL) return;
    p->pid = pid;
    p->arrival_time = arrival_time;
    p->burst_time = burst_time;
    p->priority = priority;
    process_reset_runtime(p);
}

void process_reset_runtime(Process *p)
{
    if (p == NULL) return;
    p->remaining_time = p->burst_time;
    p->started = 0;
    p->completed = 0;
    p->first_start_time = PROCESS_NOT_SET;
    p->completion_time = PROCESS_NOT_SET;
    p->turnaround_time = PROCESS_NOT_SET;
    p->waiting_time = PROCESS_NOT_SET;
    p->response_time = PROCESS_NOT_SET;
}

int process_validate(const Process *p)
{
    if (p == NULL) return 0;
    if (p->pid < 0) return 0;
    if (p->arrival_time < 0) return 0;
    if (p->burst_time <= 0) return 0;
    return 1;
}

int processes_have_unique_pids(const Process processes[], size_t count)
{
    if (processes == NULL || count == 0) return 0;
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (processes[i].pid == processes[j].pid) return 0;
        }
    }
    return 1;
}