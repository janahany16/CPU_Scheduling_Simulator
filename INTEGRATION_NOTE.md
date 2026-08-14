# Integration Note

The handbook's example structure uses `process.h/.c`, `fcfs.c`, `srtf.c`, `timeline.c/.h`, and other shared modules. Filenames are examples, not compulsory.

This branch provides a complete Process Model/Input + FCFS/SRTF baseline. Before merging into the team's `main`, the team should use ONE shared `Process` definition and ONE shared timeline interface. If the existing `timeline.*` or future Process Model differs, adapt the two scheduler modules to that agreed interface rather than keeping duplicate definitions.

Do not replace the team's `metrics.*` or `display.*` files with this branch's files; those remain owned by their respective contributors.
