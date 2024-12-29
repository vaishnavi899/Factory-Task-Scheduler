#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

typedef struct {
    int id;                 // Task ID
    char type[20];          // Task type: real-time, batch, etc.
    int arrival_time;       // Arrival time
    int burst_time;         // Burst time
    int remaining_burst;    // Remaining burst time (for RR)
    int priority;           // Priority (lower value = higher priority)
    int start_time;         // Start time (for Gantt chart)
    int completion_time;    // Completion time
    int waiting_time;       // Waiting time
    int turnaround_time;    // Turnaround time
    int remaining_time;
} Task;
void display_welcome_message() {
    printf("\n==============================================\n");
    printf("        Welcome to Factory Task Scheduler       \n");
    printf("==============================================\n");
    printf("Choose the right scheduling algorithm for your tasks\n");
    printf("and optimize task management effectively!\n");
    printf("==============================================\n\n");
}
// Function prototypes
void priority(Task tasks[], int n);
void round_robin(Task tasks[], int n, int quantum);
void fcfs(Task tasks[], int n);
void calculate_metrics(Task tasks[], int n);
void display_gantt_chart(Task tasks[], int n);
void sort_by_arrival_and_priority(Task tasks[], int n);
void sort_by_arrival(Task tasks[], int n);
void reset_remaining_burst(Task tasks[], int n);

int main() {
  display_welcome_message();
    int n, quantum;

    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];

    // Ask for task type once for all tasks
    printf("Enter task type for all tasks (real-time/batch/emergency/priority): ");
    char task_type[20];
    scanf("%s", task_type);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter details for Task %d\n", tasks[i].id);
        strcpy(tasks[i].type, task_type);  // Set the same task type for all tasks
        printf("Arrival Time: ");
        scanf("%d", &tasks[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &tasks[i].burst_time);

        if (strcmp(task_type, "emergency") == 0 || strcmp(task_type, "priority") == 0) {
            printf("Priority (1=highest): ");
            scanf("%d", &tasks[i].priority);
        } else {
            tasks[i].priority = 0;  // Default value for non-priority tasks
        }

        tasks[i].remaining_burst = tasks[i].burst_time; // For Round Robin
        tasks[i].start_time = 0;
        tasks[i].completion_time = 0;
        tasks[i].waiting_time = 0;
        tasks[i].turnaround_time = 0;
    }

    // Decide the scheduling algorithm based on task type
    if (strcmp(task_type, "emergency") == 0 || strcmp(task_type, "priority") == 0) {
        printf("\nUsing Priority Scheduling for all tasks:\n");
        priority(tasks, n);  // For emergency or priority tasks, use Priority Scheduling
        calculate_metrics(tasks, n);
        display_gantt_chart(tasks, n);
    } else if (strcmp(task_type, "batch") == 0) {
        printf("\nUsing FCFS Scheduling for all tasks:\n");
        fcfs(tasks, n);  // For batch tasks, use FCFS
        calculate_metrics(tasks, n);
        display_gantt_chart(tasks, n);
    } else if (strcmp(task_type, "real-time") == 0) {
        printf("\nUsing Round Robin Scheduling for all tasks:\n");
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &quantum);
        round_robin(tasks, n, quantum);  // For real-time tasks, use Round Robin
    } else {
        printf("Invalid task type.\n");
    }

    return 0;
}


// Sorting tasks by arrival time and priority (for Priority Scheduling)
void sort_by_arrival_and_priority(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].arrival_time > tasks[j + 1].arrival_time ||
               (tasks[j].arrival_time == tasks[j + 1].arrival_time && tasks[j].priority > tasks[j + 1].priority)) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

// Sorting tasks by arrival time (for FCFS and Round Robin)
void sort_by_arrival(Task tasks[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].arrival_time > tasks[j + 1].arrival_time) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

// Priority Scheduling Algorithm
void priority(Task tasks[], int n) {
    sort_by_arrival_and_priority(tasks, n);
    int current_time = 0, completed = 0;
    bool visited[n];
    memset(visited, 0, sizeof(visited));

    while (completed < n) {
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && tasks[i].arrival_time <= current_time) {
                if (highest_priority == -1 || tasks[i].priority < tasks[highest_priority].priority) {
                    highest_priority = i;
                }
            }
        }

        if (highest_priority == -1) {
            current_time++;
            continue;
        }

        tasks[highest_priority].start_time = current_time;
        tasks[highest_priority].completion_time = current_time + tasks[highest_priority].burst_time;
        current_time = tasks[highest_priority].completion_time;
        visited[highest_priority] = true;
        completed++;
    }
}

// FCFS Scheduling Algorithm
void fcfs(Task tasks[], int n) {
    sort_by_arrival(tasks, n);
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        // Task starts when it arrives or when the CPU is free
        if (tasks[i].arrival_time > current_time) {
            current_time = tasks[i].arrival_time;  // CPU idle until the task arrives
        }

        tasks[i].start_time = current_time;
        tasks[i].completion_time = current_time + tasks[i].burst_time;
        current_time = tasks[i].completion_time;
    }
}

// Round Robin Scheduling Algorithm
void round_robin(Task tasks[], int n, int quantum) {
    int time = 0;       // Current time
    int completed = 0;  // Count of completed tasks
    int i;

    // Initialize remaining_time for all tasks
    for (i = 0; i < n; i++) {
        tasks[i].remaining_time = tasks[i].burst_time;
    }

    printf("Gantt Chart:\n");

    while (completed < n) {
        int executed = 0; // Flag to check if a task was executed in this cycle

        for (i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                executed = 1; // Task is executed in this round
                printf("| T%d ", tasks[i].id);

                if (tasks[i].remaining_time <= quantum) {
                    // If remaining time is less than or equal to quantum
                    time += tasks[i].remaining_time;
                    tasks[i].remaining_time = 0;
                    completed++;
                    tasks[i].turnaround_time = time;
                    tasks[i].waiting_time = tasks[i].turnaround_time - tasks[i].burst_time;
                } else {
                    // If remaining time is greater than quantum
                    time += quantum;
                    tasks[i].remaining_time -= quantum;
                }
            }
        }

        if (!executed) break; // No tasks left to execute
    }

    printf("|\n");
    printf("Final time: %d\n\n", time);

    // Calculate and display AWT and ATAT
    double total_waiting_time = 0, total_turnaround_time = 0;

    printf("Task\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        total_waiting_time += tasks[i].waiting_time;
        total_turnaround_time += tasks[i].turnaround_time;
        printf("T%d\t%d\t\t%d\t\t%d\n",
               tasks[i].id, tasks[i].burst_time, tasks[i].waiting_time, tasks[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}



// Metrics Calculation: Waiting and Turnaround Time
void calculate_metrics(Task tasks[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nTask Details (ID, Type, Arrival, Burst, Priority, Start, Completion, Waiting, Turnaround):\n");
    for (int i = 0; i < n; i++) {
        tasks[i].turnaround_time = tasks[i].completion_time - tasks[i].arrival_time;
        tasks[i].waiting_time = tasks[i].start_time - tasks[i].arrival_time;  // Corrected waiting time calculation

        total_waiting_time += tasks[i].waiting_time;
        total_turnaround_time += tasks[i].turnaround_time;

        printf("T%d   %s   %d   %d   %d   %d   %d   %d   %d\n",
               tasks[i].id, tasks[i].type, tasks[i].arrival_time, tasks[i].burst_time,
               tasks[i].priority, tasks[i].start_time, tasks[i].completion_time,
               tasks[i].waiting_time, tasks[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

// Display Gantt Chart
void display_gantt_chart(Task tasks[], int n) {
    printf("\nGantt Chart:\n");

    // Print task IDs
    for (int i = 0; i < n; i++) {
        printf("|  T%d  ", tasks[i].id);
    }
    printf("|\n");

    // Print time intervals
    printf("%d", tasks[0].start_time);
    for (int i = 0; i < n; i++) {
        printf("      %d", tasks[i].completion_time);
    }
    printf("\n");
}