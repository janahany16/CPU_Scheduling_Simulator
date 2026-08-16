#include <stdio.h>
#include "priority.h"


/* Reset process data */
void resetProcesses(
    Process processes[],
    int count
)
{
    if (processes == NULL)
    {
        return;
    }

    for (int i = 0; i < count; i++)
    {
        processes[i].remaining_time =
            processes[i].burst_time;

        processes[i].started = 0;
        processes[i].completed = 0;

        processes[i].first_start_time =
            PROCESS_NOT_SET;

        processes[i].completion_time =
            PROCESS_NOT_SET;

        processes[i].turnaround_time =
            PROCESS_NOT_SET;

        processes[i].waiting_time =
            PROCESS_NOT_SET;

        processes[i].response_time =
            PROCESS_NOT_SET;
    }
}


/* Reset timeline */
void resetTimeline(
    Timeline *timeline
)
{
    if (timeline == NULL)
    {
        return;
    }

    timeline->count = 0;
}


/* Add an execution segment */
int addTimelineEntry(
    Timeline *timeline,
    int startTime,
    int endTime,
    int pid
)
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

    timeline->entries[timeline->count].startTime =
        startTime;

    timeline->entries[timeline->count].endTime =
        endTime;

    timeline->entries[timeline->count].pid =
        pid;

    timeline->count++;

    return 1;
}


/* Compare two processes by Priority rules */
static int hasHigherPriority(
    const Process *a,
    const Process *b
)
{
    /* Smaller priority number wins */
    if (a->priority != b->priority)
    {
        return a->priority < b->priority;
    }

    /* Earlier arrival time wins */
    if (a->arrival_time != b->arrival_time)
    {
        return a->arrival_time < b->arrival_time;
    }

    /* Smaller PID wins */
    return a->pid < b->pid;
}


/* Find the best ready process */
static int findBestReadyProcess(
    const Process processes[],
    int count,
    int current_time
)
{
    int best = -1;

    for (int i = 0; i < count; i++)
    {
        /* Process has not arrived */
        if (processes[i].arrival_time > current_time)
        {
            continue;
        }

        /* Process has finished */
        if (processes[i].remaining_time <= 0)
        {
            continue;
        }

        /* First ready process */
        if (best == -1)
        {
            best = i;
            continue;
        }

        /* Compare with current best */
        if (hasHigherPriority(
                &processes[i],
                &processes[best]))
        {
            best = i;
        }
    }

    return best;
}


/* Find the next process arrival */
static int findNextArrival(
    const Process processes[],
    int count,
    int current_time
)
{
    int next_arrival = -1;

    for (int i = 0; i < count; i++)
    {
        /* Already arrived */
        if (processes[i].arrival_time <= current_time)
        {
            continue;
        }

        /* Already completed */
        if (processes[i].remaining_time <= 0)
        {
            continue;
        }

        /* Find the earliest future arrival */
        if (next_arrival == -1 ||
            processes[i].arrival_time < next_arrival)
        {
            next_arrival =
                processes[i].arrival_time;
        }
    }

    return next_arrival;
}


/* Find the next scheduling event */
static int findNextSchedulingEvent(
    const Process processes[],
    int count,
    int current_index,
    int current_time
)
{
    /* Time when current process finishes */
    int finish_time =
        current_time +
        processes[current_index].remaining_time;

    /* Find the next arrival */
    int next_arrival =
        findNextArrival(
            processes,
            count,
            current_time
        );

    /* No future arrivals */
    if (next_arrival == -1)
    {
        return finish_time;
    }

    /* Arrival happens before process finishes */
    if (next_arrival < finish_time)
    {
        return next_arrival;
    }

    /* Process finishes first */
    return finish_time;
}


/* Run Priority Preemptive Scheduling */
PriorityResult runPriorityPreemptive(
    Process processes[],
    int count,
    Timeline *timeline
)
{
    PriorityResult result =
    {
        0.0,
        0.0,
        0.0
    };

    if (processes == NULL ||
        timeline == NULL ||
        count == 0)
    {
        return result;
    }

    /* Reset simulation data */
    resetProcesses(
        processes,
        count
    );

    resetTimeline(
        timeline
    );

    int current_time = 0;
    int completed_count = 0;

    /* Continue until all processes finish */
    while (completed_count < count)
    {
        /* Find the best ready process */
        int selected =
            findBestReadyProcess(
                processes,
                count,
                current_time
            );

        /* CPU is idle */
        if (selected == -1)
        {
            int next_arrival =
                findNextArrival(
                    processes,
                    count,
                    current_time
                );

            if (next_arrival == -1)
            {
                break;
            }

            /* Record idle time */
            addTimelineEntry(
                timeline,
                current_time,
                next_arrival,
                IDLE_PID
            );

            current_time =
                next_arrival;

            continue;
        }

        /* Record first CPU execution */
        if (!processes[selected].started)
        {
            processes[selected].started = 1;

            processes[selected].first_start_time =
                current_time;

            /* Calculate response time */
            processes[selected].response_time =
                current_time -
                processes[selected].arrival_time;
        }

        /* Find the next event */
        int next_event =
            findNextSchedulingEvent(
                processes,
                count,
                selected,
                current_time
            );

        int execution_time =
            next_event -
            current_time;

        /* Safety check */
        if (execution_time <= 0)
        {
            break;
        }

        /* Record execution */
        if (!addTimelineEntry(
                timeline,
                current_time,
                next_event,
                processes[selected].pid))
        {
            break;
        }

        /* Update remaining time */
        processes[selected].remaining_time -=
            execution_time;

        /* Advance time */
        current_time =
            next_event;

        /* Process finished */
        if (processes[selected].remaining_time == 0)
        {
            processes[selected].completed = 1;

            processes[selected].completion_time =
                current_time;

            /* Calculate turnaround time */
            processes[selected].turnaround_time =
                processes[selected].completion_time -
                processes[selected].arrival_time;

            /* Calculate waiting time */
            processes[selected].waiting_time =
                processes[selected].turnaround_time -
                processes[selected].burst_time;

            completed_count++;
        }

        /*
         * If the process did not finish, a new process
         * arrived and the scheduler checks priorities again.
         */
    }

    /* Calculate average metrics */
    double total_waiting = 0.0;
    double total_turnaround = 0.0;
    double total_response = 0.0;

    for (int i = 0; i < count; i++)
    {
        total_waiting +=
            processes[i].waiting_time;

        total_turnaround +=
            processes[i].turnaround_time;

        total_response +=
            processes[i].response_time;
    }

    result.average_waiting_time =
        total_waiting /
        (double)count;

    result.average_turnaround_time =
        total_turnaround /
        (double)count;

    result.average_response_time =
        total_response /
        (double)count;

    return result;
}


/* Display timeline */
void displayPriorityTimeline(
    const Timeline *timeline
)
{
    if (timeline == NULL ||
        timeline->count == 0)
    {
        printf("Timeline is empty.\n");
        return;
    }

    printf("\nPriority Preemptive Timeline:\n");
    printf("---------------------------------\n");
    printf("Start\tEnd\tProcess\n");
    printf("---------------------------------\n");

    for (int i = 0;
         i < timeline->count;
         i++)
    {
        printf(
            "%d\t%d\t",
            timeline->entries[i].startTime,
            timeline->entries[i].endTime
        );

        if (timeline->entries[i].pid == IDLE_PID)
        {
            printf("IDLE\n");
        }
        else
        {
            printf(
                "P%d\n",
                timeline->entries[i].pid
            );
        }
    }
}


/* Display process results */
void displayPriorityResults(
    const Process processes[],
    int count
)
{
    if (processes == NULL ||
        count == 0)
    {
        return;
    }

    printf("\nPriority Preemptive Results:\n");

    printf(
        "PID\tAT\tBT\tPriority\tCT\tTAT\tWT\tRT\n"
    );

    printf(
        "-------------------------------------------------------------\n"
    );

    for (int i = 0; i < count; i++)
    {
        printf(
            "P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].priority,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time,
            processes[i].response_time
        );
    }
}


/* Display average metrics */
void displayPriorityAverages(
    PriorityResult result
)
{
    printf("\n");

    printf(
        "Average Waiting Time    = %.2f\n",
        result.average_waiting_time
    );

    printf(
        "Average Turnaround Time = %.2f\n",
        result.average_turnaround_time
    );

    printf(
        "Average Response Time   = %.2f\n",
        result.average_response_time
    );
}