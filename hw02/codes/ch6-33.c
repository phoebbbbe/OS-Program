#include <sys/types.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <time.h>

typedef struct {
    int arr_len;
} args_struct;

double g_PI = 0.0;

void* monteCarlo(void* v_as) { 
    args_struct* as = v_as;
    int arr_len = (*as).arr_len;
    for (int i = 0; i < arr_len; i++) {
        double random_x = rand()/(double)RAND_MAX;
        double random_y = rand()/(double)RAND_MAX;
        g_PI += random_x * random_x + random_y * random_y <= 1; 
    }
    pthread_exit(0); 
}
int main(int arge, char* argv[]) { 
    int i;
    void* v_args;
    args_struct* args = malloc(sizeof(args_struct));
    double pi = 0;
    int num_threads = 50;
    pthread_t thread[num_threads];
    srand(time(NULL));
    if (arge != 2) {
        printf ("ERROR\n"); 
        exit(1);
    }
    int len = atoi(argv[1]);

    (*args).arr_len = len;
    v_args = (void*)(args);
    for (i = 0; i < num_threads; i++) {
        if (pthread_create(&thread[i], NULL, &monteCarlo, v_args) != 0) {
            printf("ERROR\n");
            exit(0); 
        }
    }
    for (i = 0; i < num_threads; i++)
        pthread_join(thread[i], NULL);
        
    pi = g_PI * 4.0/(len * num_threads);
    
    printf("Pi: %f\n", pi);
    free(args);
    return 0;
}