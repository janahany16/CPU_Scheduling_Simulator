#ifndef TIMELINE_H
#define TIMELINE_H

#define MAX_TIMELINE_ENTRIES 1000
#define IDLE_PID -1

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

/* Initialize the timeline */
void initializeTimeline(Timeline *timeline);

/* Add a new execution segment */
int addTimelineEntry(Timeline *timeline, int startTime, int endTime, int pid);

/* Display the timeline */
void displayTimeline(const Timeline *timeline);

#endif



