#include <stdio.h>

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

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival > p[j + 1].arrival ||
               (p[j].arrival == p[j + 1].arrival &&
                p[j].original_index > p[j + 1].original_index)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < p[i].arrival)
            current_time = p[i].arrival;

        int start = current_time;
        int completion = start + p[i].burst;

        p[i].waiting = start - p[i].arrival;
        p[i].turnaround = completion - p[i].arrival;

        current_time = completion;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].original_index > p[j + 1].original_index) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
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