#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum;
void *runner(void *param);

int main() {
    int num = 8;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,runner,&num);
    pthread_join(tid,NULL);
    printf("sum = %d\n",sum);

    return 0;
}

void *runner(void *param){
    int i, upper = *((int*)param);
    sum = 0;
    for (i=1;i<=upper;i++)
        sum+=i;
    pthread_exit(0);
}