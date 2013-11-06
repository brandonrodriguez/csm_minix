#include "ospex.h"
#include "glo.h"
#include "sched.h"

#include "schedproc.h"
#include "ospex.h"
#include <minix/syslib.h>
/* !OSPROJ3! */


int snapNum = 0;

void OSSendPtab(void)
{
	if(snapNum == HISTORY || !firstCall)
		return;
			
	int i;
	
	struct qh qHistCur[NR_SCHED_QUEUES];
	
	
	//Copy the queue head	
	sys_getqhead(&qHistCur, &cpuFreq);
	
	for(i = 0; i < (NR_SCHED_QUEUES); i++)
	{
		strcpy(qHist[snapNum][i].p_name, qHistCur[i].p_name);
		qHist[snapNum][i].p_endpoint = qHistCur[i].p_endpoint;
	}
	
	//Get a copy of the current scheduling process table
	sys_getproctab((struct proc *) &tmpPtab);
	
	//Check all processes
	for(i=0;i<(NR_PROCS+NR_TASKS);i++)
	{
		//Copy the process name
		strcpy(snapShotHist[snapNum][i].p_name,tmpPtab[i].p_name);
		//Copy endpoint
		snapShotHist[snapNum][i].p_endpoint = tmpPtab[i].p_endpoint;
		//Copy priority
		snapShotHist[snapNum][i].p_priority = tmpPtab[i].p_priority;
		//Copy remaining CPU time
		snapShotHist[snapNum][i].p_cpu_time_left = tmpPtab[i].p_cpu_time_left;
		// Copy flags? (What are flags? For blocked processes?)
		snapShotHist[snapNum][i].p_rts_flags = tmpPtab[i].p_rts_flags;
		//PI Has queue head but proc does not.
		//Queue head copy goes here	if needed
		
		//Copy NextReady
		if(tmpPtab[i].p_nextready)
		{
			//Copy the process
			sys_vircopy(SYSTEM,(vir_bytes) tmpPtab[i].p_nextready, SELF,(vir_bytes) &nextProc,sizeof(struct proc));
			//Copy name
			strcpy(snapShotHist[snapNum][i].p_nextready,nextProc.p_name);
			//Copy next processes endpoint
			snapShotHist[snapNum][i].p_nextready_endpoint = nextProc.p_endpoint;
		}
		else
		{
			//Copy no Name and -1 for endpoint
			strcpy(snapShotHist[snapNum][i].p_nextready, NOPROC);
			snapShotHist[snapNum][i].p_nextready_endpoint = -1;
		}
		
		//Copy the p_accounting
		sys_vircopy(SYSTEM,(vir_bytes) &tmpPtab[i].p_accounting, SELF,(vir_bytes) &(snapShotHist[snapNum][i].p_times) ,sizeof(struct p_accounting));
		//Copy user time
		snapShotHist[snapNum][i].p_user_time = tmpPtab[i].p_user_time;
		//Copy sys time
		snapShotHist[snapNum][i].p_sys_time = tmpPtab[i].p_sys_time;
		//Copy cycles
		snapShotHist[snapNum][i].p_cycles = tmpPtab[i].p_cycles;
		
	}
	//Incr number of snapshots taken
	snapNum++;

}
