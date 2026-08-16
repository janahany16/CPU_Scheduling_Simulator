#ifndef TIMELINE_H
#define TIMELINE_H

#include <stddef.h>

#define TIMELINE_MAX_SEGMENTS 1000
#define TIMELINE_IDLE_PID (-1)

typedef struct {
    int start;
    int end;
    int pid;
} TimelineSegment;

typedef struct {
    TimelineSegment segments[TIMELINE_MAX_SEGMENTS];
    size_t count;
} Timeline;

void timeline_init(Timeline *timeline);
int timeline_add(Timeline *timeline, int start, int end, int pid);
void timeline_print(const Timeline *timeline);

#endif