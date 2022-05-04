#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define philosopher 5
#define left (i+4)%5
#define right (i+1)%5

enum state{
    thinking = 0,
    hungry = 1,
    eating = 2,
};
int state_array[philosopher];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *putdown(int i);
void *eat(int i);

void test(int i){

    pthread_mutex_lock(&mutex);

    if((state_array[i] == hungry) &&
       (state_array[left] != eating) &&
       (state_array[right] != eating)){
            state_array[i] = eating;
            eat(i);
       }else{
            pthread_mutex_unlock(&mutex);
       }

}

void *pickup(int i){

    printf("%d\n", state_array[i]);
    state_array[i] = hungry;

    test(i);
    if(state_array[i] != eating){

    }

}

void *putdown(int i){

    state_array[i] = thinking;
    printf("putdown %d\n", i);
    pthread_mutex_unlock(&mutex);
    test(left);
    test(right);

}

void *eat(int i){

    printf("I am philosopher %d\n\
           I am eating\n", i);
    sleep(1);
    putdown(i);

}

int main(){

    pthread_t threads[philosopher];

    for(int i=0; i<philosopher; i++){
        state_array[i] = thinking;
    }

    for(int i=0; i<philosopher; i++){
        printf("pickup %d\n", i);
        pthread_create(&threads[i%5], NULL, pickup, i%5);
    }

    for(int i=0; i<philosopher; i++){
        pthread_join(threads[i], NULL);
    }

    printf("saved");

    return 0;

}
