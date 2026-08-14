# Viva Notes — First Two Work Packages

## What did I implement?
Process Model + Input Subsystem, Algorithm 1 FCFS, and Algorithm 2 SRTF.

## Process model
Original input: PID, Arrival Time, Burst Time, Priority.
Runtime state: Remaining Time, started/completed.
Statistics: first start, completion, turnaround, waiting, response.

## Why keep original and runtime state separate?
Because Compare All Algorithms must run every scheduler on the same original workload. One scheduler must not modify the data used by another.

## FCFS
Earliest arrival first, ties by smaller PID. Non-preemptive. If no process has arrived, record CPU IDLE.

## SRTF
Choose the ready process with the smallest remaining time. Reconsider when a new process arrives. Preempt only when the new ready process has a strictly smaller scheduling value. Ties use arrival time then PID.

## Official formulas
TAT = CT - AT
WT = TAT - BT
RT = First CPU Execution Time - AT
