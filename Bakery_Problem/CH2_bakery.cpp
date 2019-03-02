#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define NUM_THREADS 10

pthread_t thread[NUM_THREADS];
int count_num = 0;

struct Bakery_Lock{
    Bakery_Lock(int m){
        n = m;
        flag = new bool[n];
        label = new int[n];
        for(int i=0; i<n; i++){
            flag[i] = 0;
            label[i] = 0;
        }
    }
    void lock(int thread_id) {
        int i = thread_id;
        flag[i] = true;
        long long max = label[0];
        for (int j = 1; j < n; j ++) {
            if (label[j] > max) {
                max = label[j];
            }
        }
        label[i] = max+1;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            } else {
                while (flag[j] && ((label[j] < label[i]) || (label[i] == label[j] && j < i))) {};
            }
        }
    }

    void unlock(int thread_id){
        int i = thread_id;
        flag[i] = false;
    }
private:
    int n;
    bool *flag;
    int *label;

};

Bakery_Lock my_lock(NUM_THREADS);

void* counting(void *arg){
    int *id_ptr = (int*) arg;
    int id = *id_ptr;
    for(int i = 0; i < 1000; i++){
        my_lock.lock(id);
        count_num++;
        my_lock.unlock(id);
    }

    //wait all thread finish
    sleep(5);
    printf("thread_id: %d, count: %d\n", id, count_num);
    return nullptr;
}

int main(){
    int id[NUM_THREADS];
    for(int i=0; i<NUM_THREADS; i++){
        id[i] = i;
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&thread[i], NULL, counting, &id[i]);
    }
    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(thread[i],0);
    }
    printf("global count_num: %d\n",count_num);
    
    return 0;
}
