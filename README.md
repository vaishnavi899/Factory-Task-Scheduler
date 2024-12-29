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

## Example Input

Enter the number of tasks: 3
Enter task type for all tasks (real-time/batch/emergency/priority): priority

Enter details for Task 1:
Arrival Time: 0
Burst Time: 4
Priority (1=highest): 1

Enter details for Task 2:
Arrival Time: 2
Burst Time: 3
Priority (1=highest): 2

Enter details for Task 3:
Arrival Time: 4
Burst Time: 1
Priority (1=highest): 3


## Example Output

Using Priority Scheduling for all tasks:

Task Details (ID, Type, Arrival, Burst, Priority, Start, Completion, Waiting, Turnaround):
T1   priority   0   4   1   0   4   0   4
T2   priority   2   3   2   4   7   2   5
T3   priority   4   1   3   7   8   3   4

Average Waiting Time: 1.67
Average Turnaround Time: 4.33

Gantt Chart:
|  T1  |  T2  |  T3  |
0      4      7      8


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
- factory_task_scheduler.c: Main program code.
- README.md: Documentation for the project.

## Future Enhancements
- Add support for additional scheduling algorithms like Shortest Job First (SJF).
- Introduce dynamic task types and interactive menus.
- Extend visualization to include idle times in the Gantt chart.
