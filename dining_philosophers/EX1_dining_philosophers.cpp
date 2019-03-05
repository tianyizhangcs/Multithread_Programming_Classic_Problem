#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHER 5
#define NUM_CHOPSTICK 5
pthread_t philosopher[NUM_PHILOSOPHER];
pthread_mutex_t chopstick[NUM_CHOPSTICK];
pthread_mutex_t my_mutex;
std::mutex print_lock;

void eating(int id) {
    print_lock.lock();
  std::cout << "philosopher_" << id << " is eating" << std::endl;
  print_lock.unlock();
  sleep((3 + rand()) % 3);
  print_lock.lock();
  std::cout << "philosopher_" << id << " finished eating, thinking started"<< std::endl;
  print_lock.unlock();
}

void thinking(int id){
    print_lock.lock();
    std::cout<<"philosopher_"<<id<<" is thinking"<<std::endl;
    print_lock.unlock();
    sleep((5+rand())%5);
    print_lock.lock();
    std::cout<<"philosopher_"<<id<<" is hungry now, trying to eat"<<std::endl;
    print_lock.unlock();
}

void *sitting(void *arg){
    int *id_ptr = (int*) arg;
    int id = *id_ptr;
    while(true){
        thinking(id);
        pthread_mutex_lock(&my_mutex);
        pthread_mutex_lock(&chopstick[id]);
        pthread_mutex_lock(&chopstick[(id+1) % NUM_CHOPSTICK]);
        pthread_mutex_unlock(&my_mutex);
        eating(id);
        pthread_mutex_unlock(&chopstick[id]);
        pthread_mutex_unlock(&chopstick[(id+1)% NUM_CHOPSTICK]);
    }
    return nullptr;
}
int main() {
  int id[NUM_PHILOSOPHER];
  for(int i=0; i<NUM_CHOPSTICK; i++){
      pthread_mutex_init(&chopstick[i],0);
  }
  pthread_mutex_init(&my_mutex, 0);
  for(int i=0; i<NUM_PHILOSOPHER; i++){
      id[i] = i;
  }
  for (int i = 0; i < NUM_PHILOSOPHER; i++) {
    pthread_create(&philosopher[i], NULL, sitting, &id[i]);
  }
  for(int i=0; i<NUM_PHILOSOPHER; i++){
      pthread_join(philosopher[i],0);
  }
  for(int i=0; i<NUM_CHOPSTICK; i++){
      pthread_mutex_destroy(&chopstick[i]);
  }
  pthread_mutex_destroy(&my_mutex);
  return 0;
}
