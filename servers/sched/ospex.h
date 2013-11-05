#include "sched.h"
#include <minix/pi.h>

struct pi snapShotHist[HISTORY][NR_PROCS + NR_TASKS];
struct proc nextProc;
struct proc tmpPtab[NR_PROCS +NR_TASKS];

void OSSendPtab(void);
