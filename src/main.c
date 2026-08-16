#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "scheduler.h"
#include "display.h"
#include "metrics.h"

/* Global variables to save the state of our simulations */
Timeline t_fcfs, t_srtf, t_prio;
double tat_fcfs = 0, wt_fcfs = 0, rt_fcfs = 0;
double tat_srtf = 0, wt_srtf = 0, rt_srtf = 0;
double tat_prio = 0, wt_prio = 0, rt_prio = 0;

/* Helper function to run an algorithm and calculate its metrics in the background */
void run_and_save(int algo, const Process processes[], size_t count, Timeline *t, double *avg_tat, double *avg_wt, double *avg_rt) {
    Metrics m[MAX_PROCESSES];
    timeline_init(t);

    if (algo == 1) fcfs_schedule(processes, count, t);
    else if (algo == 2) srtf_schedule(processes, count, t);
    else if (algo == 3) priority_schedule(processes, count, t);

    for (size_t i = 0; i < count; i++) {
        calculateProcessMetrics(processes[i].arrival_time, processes[i].burst_time, processes[i].pid, t, &m[i]);
    }
    calculateAverageMetrics(m, count, avg_tat, avg_wt, avg_rt);
}

/* Function called every time new data is loaded */
void run_all_simulations(const Process processes[], size_t count) {
    if (count == 0) return;
    run_and_save(1, processes, count, &t_fcfs, &tat_fcfs, &wt_fcfs, &rt_fcfs);
    run_and_save(2, processes, count, &t_srtf, &tat_srtf, &wt_srtf, &rt_srtf);
    run_and_save(3, processes, count, &t_prio, &tat_prio, &wt_prio, &rt_prio);
}

int main() {
    int choice;
    Process processes[MAX_PROCESSES];
    size_t count = 0;
    char filename[256];
    char retry;

    while (1) {
        printf("\n====================================\n");
        printf(" CPU SCHEDULING SIMULATOR\n");
        printf("====================================\n");
        printf("1. Enter processes manually\n");
        printf("2. Load processes from file\n");
        printf("3. Display current workload\n");
        printf("4. Run FCFS\n");
        printf("5. Run SRTF\n");
        printf("6. Run Priority Preemptive\n");
        printf("7. Compare all algorithms\n");
        printf("8. Load another workload\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        
       if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            /* Clear the invalid characters from the input buffer */
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                while (1) {
                    if (input_manual(processes, MAX_PROCESSES, &count)) {
                        run_all_simulations(processes, count);
                        break;
                    }
                    printf("Invalid input detected. Try again? (y/n): ");
                    scanf(" %c", &retry); // space before %c absorbs the leftover newline
                    if (retry != 'y' && retry != 'Y') break;
                }
                break;
            case 2:
                while (1) {
                    printf("Enter filename (e.g., data/sample_input.txt): ");
                    scanf("%255s", filename);
                    if (input_from_file(filename, processes, MAX_PROCESSES, &count)) {
                        printf("Loaded %zu processes from %s\n", count, filename);
                        run_all_simulations(processes, count);
                        break;
                    }
                    printf("Failed to load data. Try again? (y/n): ");
                    scanf(" %c", &retry);
                    if (retry != 'y' && retry != 'Y') break;
                }
                break;
            case 3:
                if (count > 0) input_print_workload(processes, count);
                else printf("No processes loaded.\n");
                break;
            case 4:
                if (count > 0) {
                    printf("\n--- FCFS ---");
                    printGanttChart(&t_fcfs);
                    printAverageMetrics(tat_fcfs, wt_fcfs, rt_fcfs);
                } else printf("Please load data first.\n");
                break;
            case 5:
                if (count > 0) {
                    printf("\n--- SRTF ---");
                    printGanttChart(&t_srtf);
                    printAverageMetrics(tat_srtf, wt_srtf, rt_srtf);
                } else printf("Please load data first.\n");
                break;
            case 6:
                if (count > 0) {
                    printf("\n--- Priority Preemptive ---");
                    printGanttChart(&t_prio);
                    printAverageMetrics(tat_prio, wt_prio, rt_prio);
                } else printf("Please load data first.\n");
                break;
            case 7:
                if (count > 0) {
                    printf("\nAlgorithm\t\tAvg WT\tAvg TAT\tAvg RT\n");
                    printf("--------------------------------------------------\n");
                    printf("FCFS\t\t\t%.2f\t%.2f\t%.2f\n", wt_fcfs, tat_fcfs, rt_fcfs);
                    printf("SRTF\t\t\t%.2f\t%.2f\t%.2f\n", wt_srtf, tat_srtf, rt_srtf);
                    printf("Priority Preemptive\t%.2f\t%.2f\t%.2f\n", wt_prio, tat_prio, rt_prio);
                } else {
                    printf("Please load data first.\n");
                }
                break;
            case 8:
                count = 0;
                printf("Workload cleared.\n");
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}