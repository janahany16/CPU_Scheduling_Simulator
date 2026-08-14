#include <stdio.h>
#include "input.h"

static int valid_workload(const Process p[], size_t n)
{
    if (n == 0) return 0;
    if (!processes_have_unique_pids(p, n)) return 0;
    for (size_t i = 0; i < n; ++i) {
        if (!process_validate(&p[i])) return 0;
    }
    return 1;
}

int input_manual(Process processes[], size_t capacity, size_t *count)
{
    int n;
    if (processes == NULL || count == NULL || capacity == 0) return 0;

    printf("Number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || (size_t)n > capacity) {
        printf("Invalid number of processes.\n");
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int pid, at, bt, priority;
        printf("Process %d PID: ", i + 1);
        if (scanf("%d", &pid) != 1) { printf("Invalid PID.\n"); return 0; }
        printf("Arrival Time: ");
        if (scanf("%d", &at) != 1) { printf("Invalid Arrival Time.\n"); return 0; }
        printf("Burst Time: ");
        if (scanf("%d", &bt) != 1) { printf("Invalid Burst Time.\n"); return 0; }
        printf("Priority: ");
        if (scanf("%d", &priority) != 1) { printf("Invalid Priority.\n"); return 0; }
        process_init(&processes[i], pid, at, bt, priority);
    }

    if (!valid_workload(processes, (size_t)n)) {
        printf("Invalid workload: check unique PIDs, AT >= 0 and BT > 0.\n");
        return 0;
    }
    *count = (size_t)n;
    return 1;
}

int input_from_file(const char *filename, Process processes[], size_t capacity, size_t *count)
{
    FILE *fp;
    int n;
    if (filename == NULL || processes == NULL || count == NULL || capacity == 0) return 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open input file: %s\n", filename);
        return 0;
    }

    if (fscanf(fp, "%d", &n) != 1 || n <= 0 || (size_t)n > capacity) {
        printf("Invalid number of processes in file.\n");
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < n; ++i) {
        int pid, at, bt, priority;
        if (fscanf(fp, "%d %d %d %d", &pid, &at, &bt, &priority) != 4) {
            printf("Invalid process record at line %d.\n", i + 2);
            fclose(fp);
            return 0;
        }
        process_init(&processes[i], pid, at, bt, priority);
    }
    fclose(fp);

    if (!valid_workload(processes, (size_t)n)) {
        printf("Invalid workload: check unique PIDs, AT >= 0 and BT > 0.\n");
        return 0;
    }
    *count = (size_t)n;
    return 1;
}

void input_print_workload(const Process processes[], size_t count)
{
    printf("PID\tAT\tBT\tPriority\n");
    printf("--------------------------------\n");
    for (size_t i = 0; i < count; ++i) {
        printf("P%d\t%d\t%d\t%d\n", processes[i].pid,
               processes[i].arrival_time, processes[i].burst_time,
               processes[i].priority);
    }
}
