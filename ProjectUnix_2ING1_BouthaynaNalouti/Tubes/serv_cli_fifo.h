#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>


#define NMAX 10
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

struct rps{
    int pid;
    int resultat[NMAX];
};

struct quest{
    int pid;
    int n;
};


