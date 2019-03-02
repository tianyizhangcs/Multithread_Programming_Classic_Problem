// Copyright (c) 2018 Tianyi Zhang
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <fstream>
#include <atomic>

int count_num = 0;
std::atomic<bool> acquired(false);
int stop_point = 1000000;
int NUM_THREADS = 1;

struct TASlock{
    void lock(){
        while (acquired.exchange(true)){}
    }
    void unlock(){
        acquired.store(false);
    }
};

struct TTASlock{
    void lock(){
        while(true){
            while (acquired.load()){}
            if(!acquired.exchange(true))
                break;
        }
    }

    void unlock(){
        acquired.store(false);
    }
};

TASlock taSLock;
TTASlock ttaSlock;

void* counting(void *arg){
    int *id_ptr = (int*) arg;
    int id = *id_ptr;
    for(int i = 0; i < stop_point/NUM_THREADS+1; i++){
        ttaSlock.lock();
        count_num++;
        if(count_num == stop_point){
            ttaSlock.unlock();
            break;
        }
        ttaSlock.unlock();
    }
    return nullptr;
}

int main(int argc, const char *argv[]){
	std::string filename;
    if(argc == 1){
	filename = "test_ttas.txt";
    }else{
	filename = std::string("_ttas")+ argv[1]+".txt";
	}
    std::ofstream myfile;
    std::cout<<filename<<std::endl;
    myfile.open (filename);
    for(int i = 1; i < 101; i++){
        count_num = 0;
        NUM_THREADS = i;
        pthread_t thread[NUM_THREADS];
        int id[NUM_THREADS];
        for (int i = 0; i < NUM_THREADS; i++) {
            id[i] = i;
        }

        auto start_wall_clock = std::chrono::steady_clock::now();
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_create(&thread[i], NULL, counting, &id[i]);
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(thread[i], 0);
        }
        auto finish_wall_clock = std::chrono::steady_clock::now();

        float elapsed_time = (finish_wall_clock - start_wall_clock) / std::chrono::milliseconds(1);
        myfile <<i<<","<<elapsed_time<<"\n";
        std::cout << "thread number "<<i<<" counter result: " << count_num << " elapsed time: " << elapsed_time << " milliseconds"
                  << std::endl;
    }
    return 0;
}
