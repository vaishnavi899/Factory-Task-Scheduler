# Factory Task Scheduler

Welcome to the **Factory Task Scheduler**, a C-based tool designed to efficiently manage and optimize task scheduling in factory or real-time computing environments. This program supports multiple scheduling algorithms and simulates task execution using Linux processes, `fork()`, `exec()`, and IPC pipes.

---

## Features

* **Priority Scheduling**: Executes emergency and priority tasks based on their priority value (lower numbers = higher priority).
* **FCFS Scheduling**: Processes batch tasks in the order they arrive (First-Come-First-Served).
* **Round Robin Scheduling**: Shares CPU time equally among real-time tasks using a user-defined quantum.
* **Gantt Chart Visualization**: Displays the execution timeline for tasks.
* **Metrics Calculation**:

  * Waiting Time
  * Turnaround Time
  * Average Waiting Time
  * Average Turnaround Time

---

## How It Works

1. **Input Tasks**: Enter details for each task, including arrival time, burst time, and priority (if applicable).
2. **Select Scheduling Algorithm**: The program chooses the algorithm based on the task type:

   * **Emergency/Priority Tasks** → Priority Scheduling
   * **Batch Tasks** → FCFS Scheduling
   * **Real-Time Tasks** → Round Robin Scheduling
3. **Execution & Metrics**: Tasks are executed as separate processes using `fork()` and `pipe()` for communication, and task metrics are calculated.
4. **Visualization**: A Gantt chart is displayed alongside task details and computed metrics.

---

## How to Run

1. Compile the program:

```bash
gcc factory_task_scheduler.c -o scheduler
```

2. Run the program:

```bash
./scheduler
```

3. Follow the on-screen instructions to:

   * Enter the number of tasks
   * Specify task type (`real-time`, `batch`, `emergency`, or `priority`)
   * Provide task details (arrival time, burst time, and priority if applicable)
   * For Round Robin, enter the time quantum

---

## Input Format

* **Task Details**:

  * Arrival Time (integer)
  * Burst Time (integer, in seconds)
  * Priority (integer, optional for emergency/priority tasks)

* **Task Type**: `real-time` | `batch` | `emergency` | `priority`

* **Quantum** (only for Round Robin): Time slice in seconds

---

## Scheduling Algorithms

### 1. Priority Scheduling

* Tasks are sorted by **arrival time** and **priority**.
* Executes the task with the **highest priority** first.
* Preemptive behavior is simulated based on process arrival.

### 2. FCFS Scheduling

* Executes tasks in the **order of arrival**.
* Simple and non-preemptive scheduling.

### 3. Round Robin Scheduling

* CPU time is shared **equally among tasks** in a cyclic order.
* Uses a **user-defined time quantum** to ensure fairness.

---

## Program Structure

### `Task` Struct

```c
typedef struct {
    int id;
    char type[20];
    int arrival_time;
    int burst_time;
    int remaining_burst;
    int priority;
    int start_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    pid_t pid;
} Task;
```

* Stores task attributes, process IDs, and computed metrics.

### Key Functions

* `void priority(Task tasks[], int n)` → Implements priority scheduling
* `void fcfs(Task tasks[], int n)` → Implements FCFS scheduling
* `void round_robin(Task tasks[], int n, int quantum)` → Implements Round Robin
* `void run_process(Task *task)` → Simulates execution using `fork()`, `pipe()`, and `sleep()`
* `void calculate_metrics(Task tasks[], int n)` → Calculates waiting & turnaround times
* `void display_gantt_chart(Task tasks[], int n)` → Displays task execution timeline
* `void sort_by_arrival(Task tasks[], int n)` → Sorts tasks by arrival time
* `void sort_by_arrival_and_priority(Task tasks[], int n)` → Sorts tasks by arrival & priority

---

## Files

* `factory_task_scheduler.c` → Main C program
* `README.md` → Project documentation

---

## Example Output

```text
Enter the number of tasks: 3
Enter task type for all tasks (real-time/batch/emergency/priority): priority
Enter details for Task 1
Arrival Time: 0
Burst Time (in seconds): 4
Priority (1=highest): 2
Enter details for Task 2
Arrival Time: 1
Burst Time (in seconds): 3
Priority (1=highest): 1
Enter details for Task 3
Arrival Time: 2
Burst Time (in seconds): 2
Priority (1=highest): 3

Using Priority Scheduling for all tasks:
Task 1 finished (PID 12345)
Task 2 finished (PID 12346)
Task 3 finished (PID 12347)

Gantt Chart:
|  T1  |  T2  |  T3  |
0      4      7      9

Average Waiting Time: 2.33
Average Turnaround Time: 5.33
```

---

## Gantt Chart Visualization

Here’s an example of how the Gantt chart is represented visually:

```
Time →  0      4      7      9
        |  T1  |  T2  |  T3  |
```

* Each task block (`T1`, `T2`, `T3`) represents the execution duration of the task.
* The numbers above show the **start and end times** of each task.
* For **Round Robin**, blocks will repeat for each time slice, e.g.:

```
Time → 0   2   4   6   7
        | T1 | T2 | T1 | T3 |
```

---

## Future Enhancements

* Add additional algorithms like **Shortest Job First (SJF)** and **Multilevel Queue Scheduling**.
* Introduce **dynamic task types** and interactive menus for better UX.
* Extend Gantt chart to **show CPU idle times**.
* Include **real-time preemption support** for emergency tasks.

---


