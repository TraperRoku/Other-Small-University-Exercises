// PS IS1 320 LAB02 
// Filip Kaźmierczak 
// kf53844@zut.edu.pl


CC = gcc
CFLAGS = -O3 -g
OUTPROG = printLoginUser

all: $(OUTPROG)

$(OUTPROG): 53844.ps.lab02.main.o 53844.ps.lab02.lib.o
	$(CC) $(CFLAGS) -o $@ $^

53844.ps.lab02.main.o: 53844.ps.lab02.main.c
	$(CC) $(CFLAGS) -c 53844.ps.lab02.main.c -o $@

53844.ps.lab02.lib.o: 53844.ps.lab02.lib.c
	$(CC) $(CFLAGS) -c 53844.ps.lab02.lib.c -o $@


