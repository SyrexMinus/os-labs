#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    for(int line_width = 1; line_width <= 2*n - 1; line_width += 2)
    {
        int indent = (2*n-1-line_width) / 2;
        for(int k = 0; k < indent; k++)
        {
            printf(" ");
        }
        for(int k = 0; k < line_width; k++)
        {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}