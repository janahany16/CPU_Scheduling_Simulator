#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include "process.h"

#define MAX_PROCESSES 100

/* Interactive input. Returns 1 on success, 0 on invalid input/EOF. */
int input_manual(Process processes[], size_t capacity, size_t *count);

/* File format: first line N; then PID ArrivalTime BurstTime Priority. */
int input_from_file(const char *filename, Process processes[], size_t capacity, size_t *count);

void input_print_workload(const Process processes[], size_t count);

#endif