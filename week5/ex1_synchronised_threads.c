#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


/* Function to be executed by threads */
void *print_message_function( void *ptr );


int main(int argc, char *argv[])
{
    /* Number of threads to be created */
    int n = atoi(argv[1]);

    pthread_t * threads[100];

    /* Create independent threads each of which will execute function */
    for(int i = 0; i < n; i++) {
        printf("Creating thread %d \n", i);

        threads[i] = (pthread_t *) malloc(sizeof(pthread_t));
        int * thread_id = (int *)malloc(sizeof(int));
        *thread_id = i;

        pthread_create(threads[i], NULL, print_message_function, (void *) thread_id);

        /* Wait till threads are complete before main continues. Unless we  */
        /* wait we run the risk of executing an exit which will terminate   */
        /* the process and all threads before the threads have completed.   */
        pthread_join(*threads[i], NULL);
        free(threads[i]);
        printf("Terminating of thread %d\n", i);
    }

    return 0;
}


void *print_message_function( void *ptr )
{
    int *thread_id;
    thread_id = (int *) ptr;
    printf("Hello from thread %d \n", *thread_id);
    free(thread_id);
    return NULL;
}
