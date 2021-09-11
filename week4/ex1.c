#include <stdio.h>
#include <unistd.h>

int main() {
    int n = 42;
    int parent_PID = getpid();
    printf("Hello from parent [%d - %d]\n", parent_PID, n);

    fork();

    int current_PID = getpid();
    if (current_PID != parent_PID) {
        printf("Hello from child [%d - %d]\n", current_PID, n);
    }
    return 0;
}
