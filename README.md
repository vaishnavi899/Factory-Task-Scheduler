# Factory Task Scheduler

Welcome to the Factory Task Scheduler, a tool designed to efficiently manage and optimize task scheduling in factory environments. This program allows you to schedule tasks using various algorithms such as Priority Scheduling, First-Come-First-Served (FCFS), and Round Robin, depending on task types like real-time, batch, emergency, or priority.

## Features
- Priority Scheduling: For emergency and priority tasks, where lower priority values are executed first.
- FCFS Scheduling: Processes tasks in the order of their arrival for batch tasks.
- Round Robin Scheduling: Ensures fair time-sharing for real-time tasks with user-defined quantum.
- Displays Gantt Chart for task execution visualization.
- Calculates and displays metrics such as:
  - Waiting Time
  - Turnaround Time
  - Average Waiting Time
  - Average Turnaround Time

## How It Works
1. Input Tasks: Enter details like arrival time, burst time, and priority (if applicable) for each task.
2. Choose Scheduling Algorithm: The program selects the scheduling algorithm based on the task type:
   - Emergency/Priority: Uses Priority Scheduling.
   - Batch: Uses FCFS Scheduling.
   - Real-Time: Uses Round Robin Scheduling.
3. Execution and Metrics: The program executes the tasks using the chosen algorithm and computes performance metrics.
4. Visualization: Displays a Gantt chart and task details.

## How to Run
1. Compile the program:
   gcc factory_task_scheduler.c -o scheduler.
2. Follow the on-screen instructions to input task details and select scheduling parameters.

## Input Format
- Task Details:
  - Arrival Time
  - Burst Time
  - (Optional) Priority for emergency or priority tasks.
- Task Type: Specify one of the following:
  - `real-time`
  - `batch`
  - `emergency`
  - `priority`
- Quantum: (For Round Robin only) Specify the time quantum.

## Scheduling Algorithms
### 1. Priority Scheduling
- Sorts tasks by arrival time and priority.
- Executes the task with the highest priority first.

### 2. FCFS Scheduling
- Executes tasks in the order of their arrival.
- Simple and non-preemptive.

### 3. Round Robin Scheduling
- Shares CPU time equally among tasks in a cyclic order.
- Uses a user-defined time quantum.

## Files
- Task scheduler.c: Main program code.
- README.md: Documentation for the project.

## Future Enhancements
- Add support for additional scheduling algorithms like Shortest Job First (SJF).
- Introduce dynamic task types and interactive menus.
- Extend visualization to include idle times in the Gantt chart.
