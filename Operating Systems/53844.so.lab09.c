// SO IS1 224A LAB09
// Filip Kaźmierczak
// kf53844@zut.edu.pl
#include <stdio.h>
#include <windows.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "\nZla ilosc argumentow\n\n");
        return 1;
    }

    int dlugosc = 0;

    while (argv[1][dlugosc] != '\0') {
        if ((argv[1][dlugosc] < 58) && (argv[1][dlugosc] > 47)) {
            dlugosc = dlugosc + 1;
        }
        else {
            fprintf(stderr, "\nArgument nie jest od 0-9\n\n");
            return 1;
        }
    }

    if (dlugosc > 25) {
        fprintf(stderr, "\nArgument jest za dlugi\n\n");
        return 1;
    }


    if (dlugosc == 1) {
        int liczba = argv[1][0] - '0';
        return liczba;
    }
    else if (dlugosc <= 25) {
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




        STARTUPINFO si1, si2;
        PROCESS_INFORMATION pi1, pi2;
        DWORD exitCode1, exitCode2;
        char tablica1[100], tablica2[100];

        memset(&si1, 0, sizeof(si1));
        si1.cb = sizeof(si1);
        memset(&si2, 0, sizeof(si2));
        si2.cb = sizeof(si2);

        sprintf(tablica1, "%s %s", argv[0], tab1);
        sprintf(tablica2, "%s %s", argv[0], tab2);

        if (!CreateProcess(NULL, tablica1, NULL, NULL, FALSE, 0, NULL, NULL, &si1, &pi1) ||
            !CreateProcess(NULL, tablica2, NULL, NULL, FALSE, 0, NULL, NULL, &si2, &pi2)){
            fprintf(stderr, "Blad Procesu (%d).\n", GetLastError());
            return 2;
        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        GetExitCodeProcess(pi1.hProcess, &exitCode1);
        GetExitCodeProcess(pi2.hProcess, &exitCode2);

        printf("PID rodzica %ld, Argument: %s, wynik: %lu\n", GetCurrentProcessId(), tab1, exitCode1);
        printf("PID rodzica %ld, Argument: %s, wynik: %lu\n", GetCurrentProcessId(), tab2, exitCode2);

        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);
        CloseHandle(pi1.hThread);
        CloseHandle(pi2.hThread);

        return exitCode1 + exitCode2;
    }

    return 0;
}
