#include <stdio.h>
#include <limits.h>
#include <float.h>


int main()
{
    int a = INT_MAX;
    float b = FLT_MAX;
    double c = DBL_MAX;

    printf("int variable size: %lu bytes value: %d\n", sizeof(a), a);
    printf("float variable size: %lu bytes value: %f\n", sizeof(b), b);
    printf("double variable size: %lu bytes value: %f\n", sizeof(c), c);

    return 0;
}