#include <stdio.h>
#include "timeline.h"

void timeline_init(Timeline *timeline)
{
    if (timeline != NULL) timeline->count = 0;
}

int timeline_add(Timeline *timeline, int start, int end, int pid)
{
    if (timeline == NULL || start >= end) return 0;
    if (timeline->count > 0) {
        TimelineSegment *last = &timeline->segments[timeline->count - 1];
        if (last->pid == pid && last->end == start) {
            last->end = end;
            return 1;
        }
    }
    if (timeline->count >= TIMELINE_MAX_SEGMENTS) return 0;
    timeline->segments[timeline->count++] = (TimelineSegment){start, end, pid};
    return 1;
}

void timeline_print(const Timeline *timeline)
{
    if (timeline == NULL) return;
    for (size_t i = 0; i < timeline->count; ++i) {
        const TimelineSegment *s = &timeline->segments[i];
        printf("%d %d %s%d\n", s->start, s->end,
               s->pid == TIMELINE_IDLE_PID ? "IDLE" : "P", s->pid == TIMELINE_IDLE_PID ? 0 : s->pid);
    }
}
