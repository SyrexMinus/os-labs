#include <stdio.h>

int main() {
    const int RES_NUM = 3;
    const int PROC_NUM = 5;

    int E[RES_NUM], A[RES_NUM], C[PROC_NUM][RES_NUM], R[PROC_NUM][RES_NUM];
    int released[PROC_NUM];
    for(int i = 0; i < PROC_NUM; i++) {
        released[i] = 0;
    }

    /* read input */
    FILE *file;
    file = fopen("input.txt", "r");
    for(int i = 0; i < RES_NUM; i++) {
        fscanf(file, "%d", &E[i]);
    }
    for(int i = 0; i < RES_NUM; i++) {
        fscanf(file, "%d", &A[i]);
    }
    for(int i = 0; i < PROC_NUM; i++) {
        for(int k = 0; k < RES_NUM; k++) {
            fscanf(file, "%d", &C[i][k]);
        }
    }
    for(int i = 0; i < PROC_NUM; i++) {
        for(int k = 0; k < RES_NUM; k++) {
            fscanf(file, "%d", &R[i][k]);
        }
    }

    /* Banker's algorithm */
    for(int left = PROC_NUM; left > 0; left--) {
        for(int proc_id = 0; proc_id < PROC_NUM; proc_id++) {
            /* skip processes with too big requirements or released */
            int continue_ = 0;
            for(int res_id = 0; res_id < RES_NUM; res_id++) {
                if(R[proc_id][res_id] > A[res_id] || released[proc_id] == 1) {
                    /* Detect deadlock case */
                    if(proc_id == PROC_NUM - 1) {
                        for(int proc_id_ = 0; proc_id_ < PROC_NUM; proc_id_++) {
                            if(released[proc_id_] == 0) {
                                printf("%d\n", proc_id_);
                            }
                        }
                        return 0;
                    }
                    continue_ = 1;
                    break;
                }
            }
            if(continue_) {
                continue;
            }

            /* model available resources after execution of the process */
            for(int res_id = 0; res_id < RES_NUM; res_id++) {
                A[res_id] += C[proc_id][res_id];
            }
            released[proc_id] = 1;
            break;
        }
    }

    printf("No deadlock detected\n");

    return 0;
}