#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
} Process;

void sortByArrival(Process p[], int n) {
    Process temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, completed = 0, current_time = 0;
    float avg_tat = 0, avg_wt = 0;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input processes
    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    sortByArrival(p, n);

    printf("\nGantt Chart:\n");

    int gantt[MAX], gstart[MAX], gend[MAX], gindex = 0;

    while(completed < n) {
        int idx = -1;
        int min_bt = 9999;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].completed == 0) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            gstart[gindex] = current_time;
            current_time += p[idx].bt;
            gend[gindex] = current_time;
            gantt[gindex] = p[idx].pid;
            gindex++;

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].completed = 1;
            completed++;
        } else {
            current_time++;
        }
    }

    // Print Gantt chart
    printf("\n ");
    for(int i = 0; i < gindex; i++) {
        printf("  P%d   ", gantt[i]);
    }
    printf("\n");

    printf(" ");
    for(int i = 0; i < gindex; i++) {
        printf("------");
    }
    printf("-\n");

    printf("%d", gstart[0]);
    for(int i = 0; i < gindex; i++) {
        printf("     %d", gend[i]);
    }
    printf("\n");

    // Print process table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}
