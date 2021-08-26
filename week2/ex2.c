#include <stdio.h>
#include <string.h>


int main()
{
    char string_[1024];

    printf("Enter a string to revert\n> ");
    fgets(string_, 1024, stdin);

    printf("Reverse of the string: ");
    for(int i = strlen(string_) - 2; i >= 0; i--)
    {
        printf("%c", string_[i]);
    }

    return 0;
}