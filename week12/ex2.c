#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

int main ()
{
    FILE *infile;
    struct input_event input;

    infile = fopen("/dev/input/by-path/platform-i8042-serio-0-event-kbd", "r");
    if(infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    while(fread(&input, sizeof(struct input_event), 1, infile)) {
        // release or press
        if (input.type == EV_KEY && (input.value == 0 || input.value == 1)) {
            if (input.value == 0) {
                printf("RELEASED ");
            } else if (input.value == 1) {
                printf("PRESSED ");
            }
            printf("0x%04X (%d)\n", input.code, input.code);
        }
    }

    fclose(infile);

    return 0;
}
