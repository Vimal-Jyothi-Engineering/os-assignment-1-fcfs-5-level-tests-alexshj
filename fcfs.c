#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int index;   // original input order
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];
    Process sorted[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].index = i;
        sorted[i] = p[i];   // copy for sorting
    }

    // Sort COPY by arrival time (FCFS execution order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sorted[j].arrival > sorted[j + 1].arrival) {
                Process temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    // FCFS calculation
    for (int i = 0; i < n; i++) {
        if (current_time < sorted[i].arrival)
            current_time = sorted[i].arrival;

        sorted[i].waiting = current_time - sorted[i].arrival;
        sorted[i].turnaround = sorted[i].waiting + sorted[i].burst;

        current_time += sorted[i].burst;
    }

    // Copy results back to ORIGINAL input order
    for (int i = 0; i < n; i++) {
        p[sorted[i].index].waiting = sorted[i].waiting;
        p[sorted[i].index].turnaround = sorted[i].turnaround;
    }

    double total_wt = 0, total_tat = 0;

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].waiting);
        total_wt += p[i].waiting;
    }

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].turnaround);
        total_tat += p[i].turnaround;
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}