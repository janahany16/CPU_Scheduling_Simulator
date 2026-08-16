#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stddef.h>
#include "process.h"
#include "timeline.h"

int fcfs_schedule(const Process processes[], size_t count, Timeline *timeline);
int srtf_schedule(const Process processes[], size_t count, Timeline *timeline);
int priority_schedule(const Process processes[], size_t count, Timeline *timeline);

#endif