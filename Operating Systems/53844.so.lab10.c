// SO IS1 224A LAB10
// Filip Kaźmierczak
// kf53844@zut.edu.pl
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
double globalSum = 0.0;
pthread_mutex_t mutex;


long double calcFunc(int i) {
    if (i == 0) {
        return 3;
    } else if (i % 2 == 0) {
        return -4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
    } else {
        return 4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
    }
}


void *calc(void *arg) {
    int *args = (int *)arg;
    int start = args[0];
    int end = args[1];

    pthread_t Wself = pthread_self();
    printf("Thread %lxd size=%d first=%d\n", Wself, end - start, start);

    double rangeSum = 0.0;
    
      for (int i = start; i < end; i++) {
        rangeSum += calcFunc(i);
    }
    
    
    pthread_mutex_lock(&mutex);
    globalSum = globalSum + rangeSum;
    pthread_mutex_unlock(&mutex);

    printf("Thread %lxd Sum=%.20f\n", Wself, rangeSum);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Zla ilosc argumentow!");
        exit(EXIT_FAILURE);
    }

    int nLiczbaWyrazow = atoi(argv[1]);
    int watki = atoi(argv[2]);

    if (nLiczbaWyrazow > 1000000 || watki > 100 ) {
        printf("Poza zakresem\n");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[watki];
    int thread[watki][2];

    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < watki; i++) {
        thread[i][0] = i * (nLiczbaWyrazow / watki);
        
        thread[i][1] = (i + 1) * (nLiczbaWyrazow / watki);
        
        if (i == watki - 1) {
    	thread[i][1] += nLiczbaWyrazow % watki;
	}

        pthread_create(&threads[i], NULL, calc, (void *)thread[i]);
    }

    for (int i = 0; i < watki; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double czas = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nw/Threads PI=%.20f time=%.6f\n", globalSum, czas);

    globalSum = 0.0;
    clock_gettime(CLOCK_MONOTONIC, &start);

     for (int i = 0; i <= nLiczbaWyrazow; i++) {
        globalSum += calcFunc(i);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    czas = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("\nwo/Threads PI=%.20f time=%.6f\n", globalSum, czas);

    return 0;
}
