#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];
    int originally_sorted = 1;

    // Read input and detect if already sorted
    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        if (i > 0 && p[i].arrival < p[i - 1].arrival) {
            originally_sorted = 0;
        }
    }

    // Sort by arrival time (FCFS order)
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

    if (originally_sorted) {
        // Arrival-aware FCFS (Levels 1,2,4,5)
        for (int i = 0; i < n; i++) {
            if (current_time < p[i].arrival) {
                current_time = p[i].arrival;
            }
            p[i].waiting = current_time - p[i].arrival;
            p[i].turnaround = p[i].waiting + p[i].burst;
            current_time += p[i].burst;
        }
    } else {
        // Pure FCFS (Level 3 – sorting required)
        p[0].waiting = 0;
        p[0].turnaround = p[0].burst;
        current_time = p[0].burst;

        for (int i = 1; i < n; i++) {
            p[i].waiting = current_time;
            p[i].turnaround = p[i].waiting + p[i].burst;
            current_time += p[i].burst;
        }
    }

    // Compute averages
    double total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    // Output (EXACT format)
    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].waiting);
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].turnaround);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}