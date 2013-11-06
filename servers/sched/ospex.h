#include "sched.h"
#include <minix/pi.h>

struct pi snapShotHist[HISTORY][NR_PROCS + NR_TASKS];
struct proc nextProc;
struct proc tmpPtab[NR_PROCS +NR_TASKS];

struct proc q_head[NR_SCHED_QUEUES];

u64_t cpuFreq;

struct qh qHist[HISTORY][NR_SCHED_QUEUES];

int firstCall;


void OSSendPtab(void);
