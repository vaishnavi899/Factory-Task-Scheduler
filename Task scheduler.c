#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>   
#include <sys/wait.h>   
#include <sys/types.h>

#define MAX 100

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

// Functions
void priority(Task tasks[], int n);
void round_robin(Task tasks[], int n, int quantum);
void fcfs(Task tasks[], int n);
void calculate_metrics(Task tasks[], int n);
void display_gantt_chart(Task tasks[], int n);
void sort_by_arrival_and_priority(Task tasks[], int n);
void sort_by_arrival(Task tasks[], int n);

void run_process(Task *task) {
    int fd[2];
    char buffer[50];
    pipe(fd);

    task->pid = fork();
    if (task->pid == 0) {
        close(fd[0]); 
        sleep(task->burst_time);
        sprintf(buffer, "Task %d finished (PID %d)\n", task->id, getpid());
        write(fd[1], buffer, strlen(buffer) + 1);
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("%s", buffer); 
        close(fd[0]);
        wait(NULL);
    }
}

void display_welcome_message() {
    printf("\n==============================================\n");
    printf("        Welcome to Linux OS Task Scheduler      \n");
    printf("==============================================\n");
    printf("Implements FCFS, Priority, and Round Robin Scheduling\n");
    printf("using fork(), exec(), wait(), and IPC pipes.\n");
    printf("==============================================\n\n");
}

int main() {
    display_welcome_message();

    int n, quantum;
    printf("Enter the number of tasks: ");
    scanf("%d", &n);

    Task tasks[n];

    printf("Enter task type for all tasks (real-time/batch/emergency/priority): ");
    char task_type[20];
    scanf("%s", task_type);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("Enter details for Task %d\n", tasks[i].id);
        strcpy(tasks[i].type, task_type);  
        printf("Arrival Time: ");
        scanf("%d", &tasks[i].arrival_time);
        printf("Burst Time (in seconds): ");
        scanf("%d", &tasks[i].burst_time);

        if (strcmp(task_type, "emergency") == 0 || strcmp(task_type, "priority") == 0) {
            printf("Priority (1=highest): ");
            scanf("%d", &tasks[i].priority);
        } else {
            tasks[i].priority = 0;
        }

        tasks[i].remaining_burst = tasks[i].burst_time; 
        tasks[i].start_time = 0;
        tasks[i].completion_time = 0;
        tasks[i].waiting_time = 0;
        tasks[i].turnaround_time = 0;
    }
    if (strcmp(task_type, "emergency") == 0 || strcmp(task_type, "priority") == 0) {
        printf("\nUsing Priority Scheduling for all tasks:\n");
        priority(tasks, n);
        calculate_metrics(tasks, n);
        display_gantt_chart(tasks, n);
    } else if (strcmp(task_type, "batch") == 0) {
        printf("\nUsing FCFS Scheduling for all tasks:\n");
        fcfs(tasks, n);
        calculate_metrics(tasks, n);
        display_gantt_chart(tasks, n);
    } else if (strcmp(task_type, "real-time") == 0) {
        printf("\nUsing Round Robin Scheduling for all tasks:\n");
        printf("Enter time quantum (in seconds): ");
        scanf("%d", &quantum);
        round_robin(tasks, n, quantum);
    } else {
        printf("Invalid task type.\n");
    }

    return 0;
}

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
        run_process(&tasks[highest_priority]);  
        tasks[highest_priority].completion_time = current_time + tasks[highest_priority].burst_time;
        current_time = tasks[highest_priority].completion_time;
        visited[highest_priority] = true;
        completed++;
    }
}

void fcfs(Task tasks[], int n) {
    sort_by_arrival(tasks, n);
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (tasks[i].arrival_time > current_time) {
            current_time = tasks[i].arrival_time;
        }
        tasks[i].start_time = current_time;
        run_process(&tasks[i]); 
        tasks[i].completion_time = current_time + tasks[i].burst_time;
        current_time = tasks[i].completion_time;
    }
}

void round_robin(Task tasks[], int n, int quantum) {
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        tasks[i].remaining_time = tasks[i].burst_time;
    }

    printf("Gantt Chart:\n");

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_time > 0) {
                executed = 1;
                printf("| T%d ", tasks[i].id);

                if (tasks[i].remaining_time <= quantum) {
                    time += tasks[i].remaining_time;
                    tasks[i].remaining_time = 0;
                    run_process(&tasks[i]);
                    completed++;
                    tasks[i].turnaround_time = time;
                    tasks[i].waiting_time = tasks[i].turnaround_time - tasks[i].burst_time;
                } else {
                    time += quantum;
                    tasks[i].remaining_time -= quantum;
                    run_process(&tasks[i]);
                }
            }
        }
        if (!executed) break;
    }

    printf("|\nFinal time: %d\n\n", time);
}

void calculate_metrics(Task tasks[], int n) {
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("\nTask Details:\n");
    printf("ID\tType\tArrival\tBurst\tPriority\tStart\tCompletion\tWaiting\tTurnaround\n");

    for (int i = 0; i < n; i++) {
        tasks[i].turnaround_time = tasks[i].completion_time - tasks[i].arrival_time;
        tasks[i].waiting_time = tasks[i].start_time - tasks[i].arrival_time;

        total_waiting_time += tasks[i].waiting_time;
        total_turnaround_time += tasks[i].turnaround_time;

        printf("T%d\t%s\t%d\t%d\t%d\t\t%d\t%d\t\t%d\t%d\n",
               tasks[i].id, tasks[i].type, tasks[i].arrival_time, tasks[i].burst_time,
               tasks[i].priority, tasks[i].start_time, tasks[i].completion_time,
               tasks[i].waiting_time, tasks[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void display_gantt_chart(Task tasks[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("|  T%d  ", tasks[i].id);
    }
    printf("|\n%d", tasks[0].start_time);
    for (int i = 0; i < n; i++) {
        printf("      %d", tasks[i].completion_time);
    }
    printf("\n");
}
