#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int index;   // original input position
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].index = i;  // store original order
    }

    // Sort by arrival time (stable FCFS)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }

        current_time += p[i].burst;

        int completion = current_time;
        p[i].turnaround = completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
    }

    // Restore original order
    Process result[n];
    for (int i = 0; i < n; i++) {
        result[p[i].index] = p[i];
    }

    double total_wt = 0, total_tat = 0;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", result[i].pid, result[i].waiting);
        total_wt += result[i].waiting;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", result[i].pid, result[i].turnaround);
        total_tat += result[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}