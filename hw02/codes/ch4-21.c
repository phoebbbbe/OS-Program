#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

u_int32_t buffer[BUFFER_SIZE];

void *primes(void *param) {
    int *p = param;
    int n = *p;
    buffer[0] = 0;
    buffer[1] = 1;
    for (int i = 2; i < n; i++) {
        buffer[i] = buffer[i - 1] + buffer[i - 2];
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int n;
    pthread_t tid;
    pthread_attr_t attr;
    scanf("%d", &n);
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, primes, &n);
    pthread_join(tid, NULL);
    for (int i = 0; i < n; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}