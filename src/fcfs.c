#include <stdio.h>
#include <string.h>

typedef struct {
    char pid[10];
    int arrival;
    int burst;
    int waiting;
    int turnaround;
    int original_index;
} Process;

int main() {
    int n;
    scanf("%d", &n);

    Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].arrival, &p[i].burst);
        p[i].original_index = i;
    }

    // Sort by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j+1].arrival) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Compute waiting & turnaround time
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival) {
            current_time = p[i].arrival;
        }
        p[i].waiting = current_time - p[i].arrival;
        p[i].turnaround = p[i].waiting + p[i].burst;
        current_time += p[i].burst;
    }

    // Restore original input order for printing
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].original_index > p[j+1].original_index) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    // Compute averages
    double total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
    }

    // Print EXACTLY in required format
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