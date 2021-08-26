#include <stdio.h>
#include <stdlib.h>


void swap(int* fst, int* snd)
{
    int buf = *snd;
    *snd = *fst;
    *fst = buf;
}

int main()
{
    char string_[1024];

    printf("Enter first integer:\n> ");
    fgets(string_, 1024, stdin);
    int f = atoi(string_);
    printf("Enter second integer:\n> ");
    fgets(string_, 1024, stdin);
    int s = atoi(string_);

    printf("before swap:\n  first: %d\n  second: %d\n", f, s);

    swap(&f, &s);

    printf("after swap:\n  first: %d\n  second: %d\n", f, s);

    return 0;
}