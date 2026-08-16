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


Execution Instructions
Compile the program using the command above.

Run the program using ./simulator.

Use the interactive menu to load data (Option 2 -> data/sample_input.txt) and run the algorithms.

Source-File Organization
src/ - Contains all .c source files (main, algorithms, input, metrics, timeline, display).

include/ - Contains all .h header files.

data/ - Contains the primary sample workload (sample_input.txt).

tests/ - Contains 10 documented test cases covering all edge cases.

Input-File Format
The first line contains the total number of processes. Each subsequent line defines a process in the following format:
[PID] [Arrival Time] [Burst Time] [Priority]

Priority Convention
Smaller numerical value = higher priority (e.g., Priority 1 is higher than Priority 2).

Tie-Breaking Rules
Earlier arrival time wins.

If arrival times are identical, the smaller Process ID (PID) wins.

Assumptions & Known Limitations
The program assumes the input file is formatted correctly but will reject negative time values, duplicate PIDs, and zero burst times.

The system relies on a maximum timeline segment limit (TIMELINE_MAX_SEGMENTS = 1000).
