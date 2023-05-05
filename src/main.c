#include <stdio.h>
#include <stdbool.h>
#include <math.h> // pow()

#define MAX_TASKS 9

typedef struct {
    int exec_time; // (capacity/ calculation time.. etc)
    int period; 
    int priority; 
    int remaining_time; // remaining time to finish the task
    int deadline; // deadline of the task
}task; // custom struct type to store a task

task tasks[MAX_TASKS]; // an array to store the tasks or processes.

// Functions declarations
void add_task(int index); // add a new task at the given index
void display_tasks(int n); // display all tasks execution time and period
bool can_be_scheduled(double n); // check if the set of tasks can be scheduled using the RM algorithm
int gcd(int a, int b); // greatest common divisor
int lcm(int a, int b); // least common multiple
void schedule(int n); // rate monotonic algorithm

int main() {
    int nb_tasks; // number of tasks

    do{
        printf("Enter the number of tasks (max %d): ", MAX_TASKS);
        scanf("%d", &nb_tasks);
    } while(nb_tasks > MAX_TASKS && nb_tasks < 0);

    // Adding tasks
    for(int i = 0; i < nb_tasks; i++){
        add_task(i);
    }

    display_tasks(nb_tasks);
    if (can_be_scheduled((double)nb_tasks)) { 
        schedule(nb_tasks);
        display_tasks(nb_tasks);
    } else {
        printf("This set of tasks cannot be scheduled using the RM algorithm.\n");
    }

    return 0;
}

// Add a new task at the given index
void add_task(int index) {
    printf("Enter the execution time and period of task %d: ", index + 1);
    scanf("%d %d", &tasks[index].exec_time, &tasks[index].period);

    // Initialization
    tasks[index].priority = index;
    tasks[index].remaining_time = tasks[index].exec_time;
    tasks[index].deadline = tasks[index].period;
}

// Display all tasks execution time and period
void display_tasks(int n){
    printf("\nExecution time\tPeriod\tPriority\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t\t%d\t%d\n", tasks[i].exec_time, tasks[i].period, tasks[i].priority);
    }
}

// Check if the set of tasks can be scheduled
bool can_be_scheduled(double n) {
    double sum = 0;
    for(int i = 0; i < n; i++){
        sum += (double)tasks[i].exec_time / (double)tasks[i].period;
    }
    return sum <= n*(pow(2.0, 1.0/n) - 1.0) ? true : false;
}

// Calculates the greatest common divisor of a and b
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// Calculates the least common multiple of a and b
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

// Schedule tasks using the rate monotonic algorithm
void schedule(int n) {
    int s_time = 1; // scheduling time
    // calculate scheduling time which is the least common multiple of all tasks periods
    for(int i = 0; i < n; i++){
        s_time = lcm(s_time, tasks[i].period);
    }

    // ? Set task priority by period using bubble sort
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            if (tasks[j].period < tasks[i].period) {
                int tmp = tasks[i].priority;
                tasks[i].priority = tasks[j].priority;
                tasks[j].priority = tmp;
            }
        }
    }

    printf("\nTime\tTask\n");
    // pick the task with the least priority and execute it
    for(int t = 0; t < s_time; t++) {
        int gpt = -1; // ? greatest priority task
        int min_deadline = s_time;

        for(int j = 0; j < n; j++) {
            if (t % tasks[j].period == 0) {
                tasks[j].deadline = t + tasks[j].period;
                if (tasks[j].remaining_time == 0) {
                    tasks[j].remaining_time = tasks[j].exec_time;
                }
            }
            if (tasks[j].deadline <= min_deadline && tasks[j].remaining_time > 0) {
                gpt = j;
                min_deadline = tasks[j].deadline;
            }
        }

        if (gpt != -1){
            tasks[gpt].remaining_time--;
            printf("%d\tTask %d\n", t, gpt + 1);
        } else {
            printf("%d\tIdle\n", t);
        }
    }
}