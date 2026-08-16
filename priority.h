

#ifndef PRIORITY_H
#define PRIORITY_H

#define PROCESS_NOT_SET -1
#define MAX_TIMELINE_ENTRIES 1000
#define IDLE_PID -1

/* Process information */
typedef struct
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;

    int remaining_time;
    int started;
    int completed;

    int first_start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;

} Process;


/* Timeline information */
typedef struct
{
    int startTime;
    int endTime;
    int pid;

} TimelineEntry;


typedef struct
{
    TimelineEntry entries[MAX_TIMELINE_ENTRIES];
    int count;

} Timeline;


/* Scheduling results */
typedef struct
{
    double average_waiting_time;
    double average_turnaround_time;
    double average_response_time;

} PriorityResult;


/* Run Priority Preemptive */
PriorityResult runPriorityPreemptive(
    Process processes[],
    int count,
    Timeline *timeline
);


/* Reset process data */
void resetProcesses(
    Process processes[],
    int count
);


/* Reset timeline */
void resetTimeline(
    Timeline *timeline
);


/* Add timeline entry */
int addTimelineEntry(
    Timeline *timeline,
    int startTime,
    int endTime,
    int pid
);


/* Display timeline */
void displayPriorityTimeline(
    const Timeline *timeline
);


/* Display process results */
void displayPriorityResults(
    const Process processes[],
    int count
);


/* Display averages */
void displayPriorityAverages(
    PriorityResult result
);

#endif