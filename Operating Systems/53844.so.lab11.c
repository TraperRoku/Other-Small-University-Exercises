// SO IS1 210A LAB11
// Filip Kaźmierczak
// kf53844@zut.edu.pl 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

long double calcFunc(int i ){
    if (i == 0) {
        return  3;
    }
    else if (i % 2 == 0) {
        return  4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
    }
    else {
      return   4.0 / ((2 * i) * (2 * i + 1) * (2 * i + 2));
    }
}


double globalSum = 0.0;
	HANDLE mutex;

    void* calc(void* arg) {
        int* args = (int*)arg;
        int start = args[0];
        int end = args[1];

        DWORD watekId = GetCurrentThreadId();
        printf("Thread %lxd size=%d first=%d\n", watekId, end - start, start);

        double rangeSum = 0.0;

        for (int i = start; i < end; i++) {
            rangeSum += calcFunc(i);
        }

        WaitForSingleObject(mutex, INFINITE);
        globalSum += rangeSum;
        ReleaseMutex(mutex);


        printf("Thread %lxd Sum=%.20f\n", watekId, rangeSum);

        return NULL;
    }

    int main(int argc, char* argv[]) {
        if (argc != 3) {
            printf("Zla ilosc argumentow!");
            exit(EXIT_FAILURE);
        }

        int nLiczbaWyrazow = atoi(argv[1]);
        int watki = atoi(argv[2]);


        if (nLiczbaWyrazow > 1000000 || watki > 100) {
            printf("Poza zakresem\n");
            exit(EXIT_FAILURE);
        }

        mutex = CreateMutex(NULL, FALSE, NULL);

        HANDLE threads[watki];
        int thread[watki][2];

        clock_t start, end;

        start = clock();

        for (int i = 0; i < watki; i++) {
            thread[i][0] = i * (nLiczbaWyrazow / watki);
            thread[i][1] = (i + 1) * (nLiczbaWyrazow / watki);

            if (i == watki - 1) {
                thread[i][1] += nLiczbaWyrazow % watki;
            }

            threads[i] = CreateThread(NULL, 0, calc, thread[i], 0, NULL);
        }

        WaitForMultipleObjects(watki, threads, TRUE, INFINITE);

        end = clock();

        double czas = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nw/Threads PI=%.20f time=%.6f\n", globalSum, czas);

        globalSum = 0.0;

        start = clock();

        for (int i = 0; i <= nLiczbaWyrazow; i++) {
            globalSum += calcFunc(i);
        }

        end = clock();



        double czas2 = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("\nwo/Threads PI=%.20f time=%.6f\n", globalSum, czas2);

        return 0;

    }

