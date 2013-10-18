#include <stdio.h>
#include <unistd.h>

#ifndef PROCS_H
#define PROCS_H

void procs(void);

#define PROCNUM 2
extern pid_t pid_array[PROCNUM];
#endif
