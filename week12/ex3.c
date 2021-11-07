#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int main () {
    FILE *infile;
    struct input_event input;

    infile = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r");
    if(infile == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    int keys_statuses [1000];
    for(int i = 0; i < 1000; i++) {
        keys_statuses[i] = 0;
    }

    printf("Avaliable shortcuts:\n");
    printf("P + E -> \"I passed the Exam!\"\n");
    printf("C + A + P -> \"Get some cappuccino!\"\n");
    printf("K + C + U + F -> \"I failed the Exam!\"\n");

    while(fread(&input, sizeof(struct input_event), 1, infile)) {
        // release or press
        if(input.type == EV_KEY && (input.value == 0 || input.value == 1)) {
            if(input.value == 0) {
                keys_statuses[input.code] = 0;
            }
            else if(input.value == 1) {
                keys_statuses[input.code] = 1;
                // P + E
                if(keys_statuses[25] && keys_statuses[18]) {
                    printf("I passed the Exam!\n");
                }
                // C + A + P
                else if(keys_statuses[46] && keys_statuses[30] && keys_statuses[25]) {
                    printf("Get some cappuccino!\n");
                }
                // K + C + U + F
                else if(keys_statuses[33] && keys_statuses[22] && keys_statuses[46] && keys_statuses[37]) {
                    printf("I failed the Exam!\n");
                }
            }
        }
    }

    fclose(infile);

    return 0;
}
