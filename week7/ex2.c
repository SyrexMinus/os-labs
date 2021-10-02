#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char string_[1024];
    printf("Enter N:\n> ");
    fgets(string_, 1024, stdin);
    int n = atoi(string_);

    int * array = (int *) calloc(n, sizeof(int));
    for(int i = 0; i < n; i++) {
        array[i] = i;
        printf("%d ", array[i]);
    }

    free(array);

    return 0;
}
