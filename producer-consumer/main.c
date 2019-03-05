/* compile: gcc -pthread -o main main.c
 * execute: ./main 4 5 10 100
 * Name : Tianyi Zhang
 * File: main.c main
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
typedef int buffer_item;
int BUFFER_SIZE;
buffer_item* buffer=NULL;
pthread_mutex_t mutex;
sem_t full, empty;
int count=0, in, out,target_num,num_produced,num_consumed,num_prothread;
long long int timestamp_usec;


// Function prototypes
int insert_item(buffer_item item);
int remove_item(buffer_item *item);
void *consumer(void *param);
void *producer(void *param);

int main(int argc, char **argv){
    FILE *f = fopen("producer-event.log","w");
    fclose(f);
    FILE *fc = fopen("consumer-event.log", "w");
    fclose(fc);
    if (argc != 5){
        printf("ERROR: Provide exactly four arguments.\n");
        exit(1);
    }

    // Retrieve command line arguments

    const long int num_producer = strtol(argv[1], NULL, 0);
    const long int num_consumer = strtol(argv[2], NULL, 0);
    const long int buffer_size = strtol(argv[3],NULL,0);
    const long int target = strtol(argv[4],NULL,0);
    //const long int stime = strtol(argv[4], NULL, 0);
    num_prothread=num_producer;
    target_num=target;
    BUFFER_SIZE= buffer_size;
    buffer = calloc(buffer_size,sizeof(buffer_item));

    // Initialize
    int i;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE); // All of buffer is empty
    sem_init(&full, 0, 0);
    count = in = out = 0;

    // Create the producer and consumer threads
    pthread_t producers[num_producer];
    pthread_t consumers[num_consumer];
    for(i = 0; i < num_producer; i++)
        pthread_create(&producers[i], NULL, producer, i);
    for(i = 0; i < num_consumer; i++)
        pthread_create(&consumers[i], NULL, consumer, i);
    // Sleep before terminating
    //sleep(10);
    for(int i = 0; i<num_producer; i++){
        pthread_join(producers[i],NULL);
    }
    for(int i = 0; i<num_consumer; i++){
        pthread_join(consumers[i],NULL);
    }
    printf("total number of produced items: %d\n",num_produced);
    printf("total number of consumed items: %d\n",num_consumed);
    return 0;
}

// Insert item into buffer.
//Returns 0 if successful, -1 indicating error
int insert_item(buffer_item item){
    struct timeval timer_usec;
    int success;
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    // Add item to buffer
    if(num_produced<target_num){
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        timestamp_usec = (((long long int) timer_usec.tv_sec) * 1000000ll +
                         (long long int) timer_usec.tv_usec);
        count++;
        num_produced++;
        success = 0;
    }
    else
        success = -1;
    //sem_post(&full);
    return success;
}

// Remove an object from the buffer, placing it in item.
// Returns 0 if successful, -1 indicating error
int remove_item(buffer_item *item){
    struct timeval timer_usec;
    int success;
    if(num_consumed==target_num) return -1;
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    // Remove item from buffer to item
    if( count != 0){
        *item = buffer[out];
        timestamp_usec = (((long long int) timer_usec.tv_sec) * 1000000ll +
                          (long long int) timer_usec.tv_usec);
        out = (out + 1) % BUFFER_SIZE;
        count--;
        num_consumed++;
        success = 0;
    }
    else
        success = -1;
    return success;
}

void *producer(void *param){
    int thread_num= param;
    buffer_item item;
    while(1){
        sleep(rand() % 2 + 1); // Sleep randomly between 1 and 5 seconds
        item = rand();
        if(insert_item(item)){
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
            break;
        }
        else{
            FILE *f = fopen("producer-event.log", "a");
            printf("<Timestamp %lu>,<Producer>,<Thread_ID %d>,<Buffer_Index %d>,<Item %d>\n",timestamp_usec,thread_num,in,item);
            fprintf(f,"<Timestamp %lu>,<Producer>,<Thread_ID %d>,<Buffer_Index %d>,<Item %d>\n",timestamp_usec,thread_num,in,item);
            fclose(f);
            pthread_mutex_unlock(&mutex);
            sem_post(&full);
        }
    }
}


void *consumer(void *param){
    int thread_num= param+num_prothread;
    buffer_item item;
    while(1){
        sleep(rand() % 2 + 1); // Sleep randomly between 1 and 5 seconds
        if(remove_item(&item)){
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
            break;
        }
        else {
            FILE *fc = fopen("consumer-event.log", "a");
            fprintf(fc,"<Timestamp %lu>,<Consumer>,<Thread_ID %d>,<Buffer_Index %d>,<Item %d>\n", timestamp_usec,thread_num, out, item);
            fclose(fc);
            printf("<Timestamp %lu>,<Consumer>,<Thread_ID %d>,<Buffer_Index %d>,<Item %d>\n", timestamp_usec,thread_num, out, item);
            pthread_mutex_unlock(&mutex);
            sem_post(&empty);
        }
    }
}