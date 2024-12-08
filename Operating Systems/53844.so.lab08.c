// SO IS1 224A LAB08
// Filip Kazmierczak
// kf53844@zut.edu.pl
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "\nWiecej niz jeden arguemnt\n\n");
        return 1;
    }

    int dlugosc = 0;

    while (argv[1][dlugosc] != '\0') {
        if ((argv[1][dlugosc] < 58) && (argv[1][dlugosc] > 47)) {
            dlugosc = dlugosc + 1;
        } else {
            fprintf(stderr, "\nBlad nie jest zlozony z liczb od 0-9\n\n");
            return 1;
        }
    }

    if (dlugosc > 25) {
        fprintf(stderr, "\nArgument jest za dlugi!\n\n");
        return 1;
    }

    pid_t child1, child2;

    
    if (dlugosc == 1) {
        int liczba = argv[1][0] - '0';
        return liczba;
    } else if (dlugosc <= 25) {
        int polowa = dlugosc / 2;
        int reszta = dlugosc % 2;

        char tab1[polowa + 1]; 
        char tab2[polowa + reszta + 1]; 

       for (int i = 0; i < polowa; i++) {
            tab1[i] = argv[1][i];
        }

        tab1[polowa] = '\0';

         for (int j = 0; j < (polowa + reszta); j++) {
            tab2[j] = argv[1][polowa + j];
        }

       tab2[polowa + reszta] = '\0';
	child1 = fork();


        if (child1 == 0) {
           execl(argv[0], argv[0], tab1, NULL);
        }
    child2 = fork();

        if (child2 == 0) {
           execl(argv[0], argv[0], tab2, NULL);
        }

        int status1, status2;
        waitpid(child1, &status1, 0);
        waitpid(child2, &status2, 0);

        printf("Pid rodzica: %d Pid dziecka: %d, wynik: %s, oficjalny wynik: %d\n", getpid(), child1, tab1, WEXITSTATUS(status1));
        printf("Pid rodzica: %d Pid dziecka: %d, wynik: %s, oficjalny wynik: %d\n", getpid(), child2, tab2, WEXITSTATUS(status2));					

        return WEXITSTATUS(status1) + WEXITSTATUS(status2);
    }

    return 0;
}

