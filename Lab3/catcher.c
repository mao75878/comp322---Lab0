#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/times.h>
#include <stdlib.h>
#include <string.h>

static int count = 0;
static int term = 0;

int pid = getpid();
fprintf(stderr, "catcher: $$ = %d\n", pid); //The program includes a status line that includes its PID to stderr
