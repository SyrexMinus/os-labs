#include <stdio.h>
#include <stdlib.h>


struct process {
    int arrival_time;
    int burst_time;
};


int comp (const void * elem1, const void * elem2) {
    int f = ((struct process *)elem1)->arrival_time;
    int s = ((struct process *)elem2)->arrival_time;
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}


int main(void) {
    int processes_number = 0;
    struct process processes [11];

    FILE *file;
    file = fopen("input.csv", "r");
    for(int i = 0; i < 11; i++, processes_number++){
        if(fscanf(file, "%d,%d", &processes[i].arrival_time, &processes[i].burst_time) == EOF) {
            break;
        }
    }

    qsort(processes, processes_number, sizeof(*processes), comp);

    int total_turnaround_time = 0;
    int total_wait_time = 0;

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    int current_time = -1;
    for(int i = 0; i < processes_number; i++) {
        if(current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        int completion_time = current_time + processes[i].burst_time;
        int turnaround_time = completion_time - processes[i].arrival_time;
        int wait_time = current_time - processes[i].arrival_time;

        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, processes[i].arrival_time, processes[i].burst_time, completion_time,
               turnaround_time, wait_time);

        total_turnaround_time += turnaround_time;
        total_wait_time += wait_time;
        current_time = completion_time;
    }

    float avg_turnaround_time = (float) total_turnaround_time / processes_number;
    float avg_wait_time = (float) total_wait_time / processes_number;

    printf("\nAverage Turnaround Time = %f", avg_turnaround_time);
    printf("\nAverage WT = %f", avg_wait_time);

    return 0;
}