# Cover-Sheet / Rubric Checklist — Team 8, Variant 3

Source: course handbook and task-distribution sheet.

## Relevant shared marks
- Process Model: 5 marks
- Input Subsystem: 7 marks
- Scheduling Algorithm 1 (FCFS): 10 marks
- Scheduling Algorithm 2 (SRTF): 10 marks

## Process Model evidence
- [x] Process structure contains required input attributes: PID, Arrival Time, Burst Time, Priority.
- [x] Runtime state includes Remaining Time and completion/start state.
- [x] Scheduling statistics have dedicated fields.
- [x] Original values are preserved; algorithms operate on copies/runtime state.
- [x] Runtime state can be reset for another simulation.

## Input Subsystem evidence
- [x] Interactive terminal input.
- [x] File input with documented format.
- [x] Validation for positive process count, unique PID, AT >= 0, BT > 0.
- [x] Malformed/unreadable input produces an understandable message and is rejected.
- [x] Invalid workload is not passed to scheduling.

## Algorithm 1 — FCFS
- [x] Correct arrival-order scheduling.
- [x] Tie: earlier arrival, then smaller PID.
- [x] Non-preemptive behavior.
- [x] CPU idle handling.
- [x] Timeline output.
- [x] Test coverage.

## Algorithm 2 — SRTF
- [x] Smallest remaining time selection.
- [x] Reconsideration when new process arrives.
- [x] Strictly-better condition for preemption.
- [x] Tie: earlier arrival, then smaller PID.
- [x] CPU idle handling.
- [x] Timeline output.
- [x] Test coverage.

## Still owned by the rest of the team / final integration
- Algorithm 3: Priority Preemptive.
- Final shared timeline integration.
- Metrics and averages.
- Final Gantt/display.
- Compare All Algorithms.
- Full project testing, including invalid-input evidence and unseen workloads.
- Final README/report/submission package.
