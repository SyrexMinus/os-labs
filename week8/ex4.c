#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>


int main() {
    struct rusage usage;
    int gb_size = 1024*1024*1024;
    // each second during 100 seconds I allocate and fill with zeros 1 gb of memory
    // during the time memory used by the process increases rapidly
    for(int i = 0; i < 100; i++) {
        void * memory = malloc(gb_size);
        memset(memory, 0, gb_size);
        getrusage(RUSAGE_SELF, &usage);
        printf("memory usage: %ld\n", usage.ru_maxrss);
        sleep(1);
    }
    return(0);
}
