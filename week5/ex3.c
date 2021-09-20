#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


int count = 0;
const int BUFFER_SIZE = 8;
char buffer[BUFFER_SIZE];
int is_consumer_sleep = 0;
int is_producer_sleep = 0;
int race_condition_occured = 0;


/* Main loop for consumer. Consumes messages from buffer. */
void * consumer_loop(void * _);

/* Main loop for producer. Produces messages to buffer. */
void * producer_loop(void * _);


int main(void)
{
    pthread_t producer_tid, consumer_tid;

    pthread_create(&producer_tid, NULL, producer_loop, NULL);
    pthread_create(&consumer_tid, NULL, consumer_loop, NULL);

    /* Wait till threads are complete before main continues. Unless we  */
    /* wait we run the risk of executing an exit which will terminate   */
    /* the process and all threads before the threads have completed.   */
    while(!race_condition_occured);
    printf("Race condition occured\n");

    return 0;
}


void * consumer_loop(void * _) {
    while(1) {
        while(is_consumer_sleep) {
            if (is_consumer_sleep) {
                race_condition_occured = 1;
            }
        }

        if(count == 0) {
            is_consumer_sleep = 1;
            continue;
        }

        char message = buffer[count-- - 1];
        is_producer_sleep = 0;
    }
}


void * producer_loop(void * _) {
    char message[] = "Hello world!";
    char char_index = 0;

    while(1) {
        while(is_producer_sleep) {
            if (is_consumer_sleep) {
                race_condition_occured = 1;
            }
        }

        if(count == BUFFER_SIZE) {
            is_producer_sleep = 1;
            continue;
        }

        char message_to_send = message[char_index];
        char_index = (char_index + 1) % strlen(message);
        buffer[count++] = message_to_send;
        is_consumer_sleep = 0;
    }
}
