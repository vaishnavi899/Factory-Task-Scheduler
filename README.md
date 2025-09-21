# Factory Task Scheduler

Welcome to the **Factory Task Scheduler**, a Linux-based task scheduling tool designed to efficiently manage and optimize tasks in factory or real-time computing environments. This program allows scheduling using various algorithms such as **Priority Scheduling**, **First-Come-First-Served (FCFS)**, and **Round Robin**, depending on task types like real-time, batch, emergency, or priority.

---

## Features
- **Priority Scheduling:** For emergency and priority tasks, where lower priority values are executed first.
- **FCFS Scheduling:** Executes tasks in the order of arrival for batch tasks.
- **Round Robin Scheduling:** Ensures fair time-sharing for real-time tasks with a user-defined quantum.
- **Gantt Chart Visualization:** Displays task execution order and timing.
- **Metrics Calculation:** Computes and displays:
  - Waiting Time
  - Turnaround Time
  - Average Waiting Time
  - Average Turnaround Time
- **Linux Process Management:** Uses `fork()`, `pipe()`, and `wait()` for process execution and inter-process communication (IPC).

---

## How It Works
1. **Input Tasks:** Enter task details such as arrival time, burst time, and priority (if applicable).
2. **Select Scheduling Algorithm:** The program chooses the scheduling algorithm based on task type:
   - `emergency` / `priority` → **Priority Scheduling**
   - `batch` → **FCFS Scheduling**
   - `real-time` → **Round Robin Scheduling**
3. **Execute Tasks:** Tasks are executed as Linux processes using `fork()`, and results are communicated via pipes.
4. **Metrics & Visualization:** The program calculates task metrics and displays a Gantt chart.

---

## How to Run
1. **Compile the program:**
   ```bash
   gcc factory_task_scheduler.c -o scheduler
Run the program:

./scheduler


Follow on-screen instructions to enter task details, task type, and time quantum (for Round Robin).

Input Format

Task Details:

Arrival Time (integer)

Burst Time (integer, in seconds)

Priority (integer, optional for emergency/priority tasks)

Task Type: real-time, batch, emergency, or priority

Quantum: Required only for Round Robin scheduling

Scheduling Algorithms
1. Priority Scheduling

Tasks are sorted by arrival time and priority.

Executes the task with the highest priority (lowest value) first.

2. FCFS Scheduling

Tasks are executed in the order of arrival.

Simple and non-preemptive.

3. Round Robin Scheduling

Tasks share CPU time cyclically.

Uses a user-defined time quantum for execution slices.

Linux Process Integration

Each task is executed as a separate process using fork().

pipe() is used for inter-process communication to notify completion.

wait() ensures the parent process waits for child processes to finish.

Files

factory_task_scheduler.c — Main program code.

README.md — Documentation and usage guide.

Future Enhancements

Add support for additional scheduling algorithms like Shortest Job First (SJF).

Introduce dynamic task types and interactive menus.

Enhance Gantt chart visualization to include idle times.
