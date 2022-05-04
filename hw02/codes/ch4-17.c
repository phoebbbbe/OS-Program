#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>

int num = 0;

double genPoint() {
    return (double)rand() / (double)RAND_MAX;
}

void *calculatePi(void *p) {
    int total = atoi(p);
    double x, y;

    for (int i = 0; i < total; i++) {
        x = genPoint();
        y = genPoint();

        if ((x * x + y * y) < 1) {
            num++;
        }
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    int total;
    if (argc < 2)
        return 1;

    srand(time(NULL));
    pthread_t t_id;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_create(&t_id, &attr, calculatePi, argv[1]);
    pthread_join(t_id, NULL);

    total = atoi(argv[1]);
    printf("Pi : %f\n", 4 * (double)num / (double)total);
}