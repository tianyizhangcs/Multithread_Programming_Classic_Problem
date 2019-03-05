/* compile: g++ -pthread -o main main.cpp
 * execute: ./main
 * Name : Tianyi Zhang
 * File: main.cpp main
 */

#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <vector>

const int p[4][3]={{1,4,7},{6,5,2},{3,7,0},{8,1,9}},q[3][4]={{2,4,7,6},{5,6,3,3},{4,0,9,8}};
int r[4][4];
int step_i = 0;
void *runner(void *param);
#define NUM_THREADS 16

int main() {
    int i=0;
    pthread_t workers[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    while(i< NUM_THREADS){
        int* p;
        pthread_create(&workers[i],&attr,runner,(void*)(p));
        i++;
    }
    for(int i = 0; i<NUM_THREADS; i++){
        pthread_join(workers[i],NULL);
    }
    std::cout<<"multiplication result:"<<std::endl;
    for(int i=0; i<4;i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << r[i][j]<<", ";
            if(j==3) std::cout<<std::endl;
        }
    }
    return 0;
}

void *runner(void *param){
    int temp = step_i++;
    int rownum = temp/4;
    int cnum = temp%4;
    for(int c=0; c<3; c++){
        r[rownum][cnum]+=((p[rownum][c])*(q[c][cnum]));
    }
    pthread_exit(0);
}