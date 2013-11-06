/* !OSPROJ3!
 *	
 * do_getqhead
 * 
 * Request a copy of run_q_head
 * 
*/


#include "kernel/system.h"
#include <minix/pi.h>
#include <string.h>

int do_getqhead(struct proc * caller, message *m_ptr)
{
	printf("In Kernel Call\n");
	
	//Temp storage
	struct qh hist[NR_SCHED_QUEUES]; 
	u64_t cpuFreq;
	
	cpuFreq = cpu_get_freq(0);
	
	
	//Pointer 
	struct proc **head;
	head = get_cpu_var(0, run_q_head);
	
	//Copy to the local queue
	int i;
	for(i = 0; i < (NR_SCHED_QUEUES); i++)
	{
		if(head[i])
		{
			strcpy(hist[i].p_name, head[i]->p_name);
			hist[i].p_endpoint = head[i]->p_endpoint;
		} else
		{
			hist[i].p_endpoint = -1;
		}
	
	}
	
	//Copy queue
	data_copy_vmcheck(caller,
		KERNEL, (vir_bytes)&hist,
		caller->p_endpoint, (vir_bytes)m_ptr->m1_p1,
		sizeof(hist));	
		
	//Copy cpu freq
	data_copy_vmcheck(caller,
		KERNEL, (vir_bytes)&cpuFreq,
		caller->p_endpoint, (vir_bytes)m_ptr->m1_p2,
		sizeof(u64_t));
	
	
	
	return 0; 
}
