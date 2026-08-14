# Test Plan — Process Model + Input + FCFS + SRTF

The expected scheduling behavior is determined from the scheduling rules before running the program.

| ID | Category | Purpose | Expected result |
|---|---|---|---|
| T01 | All AT=0 | FCFS baseline | P1 -> P2 -> P3 for the supplied PIDs |
| T02 | Different arrivals | Processes join while CPU is busy | FCFS preserves arrival order |
| T03 | Initial idle | No process at t=0 | IDLE from 0 to first arrival |
| T04 | Idle between | Gap after a completion | IDLE segment is recorded explicitly |
| T05 | Immediate preemption | SRTF-specific behavior | Newly available shorter remaining job preempts |
| T06 | Tie | SRTF tie handling | Earlier arrival, then smaller PID |
| T07 | Initial idle | SRTF idle behavior | IDLE until first arrival |
| T08 | Idle between | SRTF gap behavior | IDLE segment is recorded explicitly |
| T09 | Single process | Boundary/simple case | One process runs after any initial idle |
| T10 | Invalid input + preservation | Validation and clean original workload | Invalid data rejected; scheduler does not modify original Process array |

The full team must additionally cover any third-algorithm-specific cases and final integration tests.
