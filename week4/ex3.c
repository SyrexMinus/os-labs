#include <stdio.h>
#include <stdlib.h>

int main() {
    while(1) {
        char string_[1024];
        printf("> ");
        fgets(string_, 1024, stdin);
        system(string_);
    }
    return 0;
}
