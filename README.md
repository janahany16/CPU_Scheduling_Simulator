# CPU_Scheduling_Simulator
# CPU Scheduling Simulator (Team XX - Variant 3)

## Team Members
* Mariam Hany Refaat - 20220473
* Zainab Abdelfattah darwish - 20230241
* Mariam Ahmed Mohammed  - 20240929
* Mazen Mohamed Sobhy - 20240768
* Hassan Abdelrahaman Hassan - 20210291
* Jana Hany Mahmoud Tawfiq - 20240256

## Assigned Variant
**Variant 3:** FCFS, SRTF, Priority Preemptive

## Compilation Command
```bash
gcc -Wall -Wextra -Iinclude src/*.c -o simulator


# Task 1 & 2 — Process Model/Input + Algorithm 1/2

This package implements the first two team work packages for Variant 3 of the CPU Scheduling Simulator:
- Process Model + Input Subsystem
- Algorithm 1: FCFS
- Algorithm 2: SRTF

The handbook requires a C multi-file design, a process model with original/runtime state, interactive and file input, validation, scheduling modules, and testing. This package is designed as a clean baseline for integration with the team's existing `timeline.c/.h`, `metrics.c/.h`, and `display.c/.h` modules.

## Process data
Original input:
`pid`, `arrival_time`, `burst_time`, `priority`

Runtime/statistics:
`remaining_time`, `started`, `completed`, `first_start_time`, `completion_time`, `turnaround_time`, `waiting_time`, `response_time`

## File input format
First line: number of processes.
Each following line:
`PID ArrivalTime BurstTime Priority`

Example: see `data/sample_input.txt`.

## Validation
- number of processes > 0
- unique PIDs
- arrival time >= 0
- burst time > 0
- malformed/unreadable input is rejected with a message

## Shared Process Model / Scheduling
Both FCFS and SRTF use the same `Process` structure from `include/process.h`. Each scheduler makes a private copy of the input workload and resets runtime fields before simulation, so the original workload remains unchanged for later algorithms.

- FCFS: earliest arrival first, then smaller PID; non-preemptive.
- SRTF: smallest remaining time; preemptive when a ready process has a strictly smaller remaining time; ties by arrival time then PID.
- CPU idle intervals are stored explicitly in the shared `Timeline`.

## Build test runner
```bash
gcc -std=c11 -Wall -Wextra -pedantic -Iinclude \
  src/process.c src/input.c src/timeline.c src/fcfs.c src/srtf.c \
  tests/test_runner.c -o test_runner
./test_runner
```

## Integration note
The schedulers do not define a second Process structure. `fcfs.c` and `srtf.c` both include `scheduler.h`, which exposes the shared `Process` and `Timeline` types. Before final integration, keep this single Process definition and connect the shared timeline to the team metrics/display modules. The example folder structure in the handbook is recommended, not compulsory.
