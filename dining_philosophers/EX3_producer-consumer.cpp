#include <iostream>
#include <pthread.h>
#include <unistd.h>

#define CAN_DOWN 0
#define CAN_UP 1
int bob_can = CAN_DOWN;
int alice_can = CAN_UP;
int food = 0;

void* bob_feed(void* arg){
    while(true){
        if(bob_can == CAN_DOWN){
            printf("Bob is putting food to the yard\n");
            sleep((1+rand())%3);
            food ++;
            printf("Bob finished putting, food status = '%d', back to his house\n", food);
            bob_can = CAN_UP;
            alice_can = CAN_DOWN;
        }
    }
    return nullptr;
}

void* alice_pet_eat(void* arg){
    while(true){
        if(alice_can == CAN_DOWN){
            printf("Alice pet is eating\n");
            sleep((1+rand())%3);
            food --;
            printf("Alice pet finished eating, food status = '%d', back to her house\n",food);
            alice_can = CAN_UP;
            bob_can = CAN_DOWN;
        }
    }
    return nullptr;
}

int main(){
    pthread_t bob;
    pthread_t alice_pet;
    pthread_create(&bob,NULL,bob_feed,nullptr);
    pthread_create(&alice_pet,NULL,alice_pet_eat,nullptr);

    pthread_join(bob,0);
    pthread_join(alice_pet,0);

    return 0;
}