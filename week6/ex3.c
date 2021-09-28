#include <stdio.h>
#include <stdlib.h>


struct process {
    int arrival_time;
    int burst_time;
    int performed_time;
    int schedule_iteration;
};


int comp (const void * elem1, const void * elem2) {
    int f = ((struct process *)elem1)->arrival_time;
    int s = ((struct process *)elem2)->arrival_time;
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}


int main(void) {
    char string_[1024];
    printf("Specify quantum:\n> ");
    fgets(string_, 1024, stdin);
    int quantum = atoi(string_);

    int processes_number = 0;
    struct process processes [11];

    FILE *file;
    file = fopen("input.csv", "r");
    for(int i = 0; i < 11; i++, processes_number++){
        if(fscanf(file, "%d,%d", &processes[i].arrival_time, &processes[i].burst_time) == EOF) {
            break;
        }
        processes[i].schedule_iteration = -1;
    }

    qsort(processes, processes_number, sizeof(*processes), comp);

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");

    int total_turnaround_time = 0;
    int total_wait_time = 0;
    int current_time = 0;
    int processes_left = processes_number;
    int k = 1;
    for(; processes_left != 0;) {
        int min_next_arrival = -1;
        int has_performed = 0;
        for(int i = 0; i < processes_number; i++) {
            // consider only not finished processes
            if(processes[i].performed_time < processes[i].burst_time) {
                // add to the cycle current processes
                if(processes[i].arrival_time <= current_time) {
                    int time_left = processes[i].burst_time - processes[i].performed_time;
                    if(time_left <= quantum) {
                        processes[i].performed_time = processes[i].burst_time;
                        current_time += time_left;

                        int completion_time = current_time;
                        int turnaround_time = completion_time - processes[i].arrival_time;
                        int wait_time = turnaround_time - processes[i].burst_time;

                        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", k, processes[i].arrival_time, processes[i].burst_time,
                               completion_time, turnaround_time, wait_time);

                        total_turnaround_time += turnaround_time;
                        total_wait_time += wait_time;
                        k += 1;
                        processes_left -= 1;
                    }
                    else {
                        processes[i].performed_time += quantum;
                        current_time += quantum;
                    }
                    has_performed = 1;
                }
                else if(min_next_arrival == -1 || min_next_arrival > processes[i].arrival_time) {
                    min_next_arrival = processes[i].arrival_time;
                }
            }
        }
        if(!has_performed && min_next_arrival != -1) {
            current_time = min_next_arrival;
        }
    }

    float avg_turnaround_time = (float) total_turnaround_time / processes_number;
    float avg_wait_time = (float) total_wait_time / processes_number;

    printf("\nAverage Turnaround Time = %f", avg_turnaround_time);
    printf("\nAverage WT = %f", avg_wait_time);

    return 0;
}
