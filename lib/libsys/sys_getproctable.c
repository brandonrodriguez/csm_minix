/* !OSPROJ3!
 *	
 * sys_getproctable(char *procPtr)
 * 
 * System call to request a copy of the proc table and store it at the 
 * address of procPtr.
 * 
 * The request will be sent to the process manager 
*/

#include "syslib.h"

#include <minix/callnr.h>	//Define for GETPROCTABLE (105)
#include <lib.h>			//Required for all lib c files
#include <minix/com.h>		//Def of _syscall
#include <minix/ipc.h> 		//Def of IPC/Message
#include <minix/pi.h>


int sys_getproctable(char *procPtr)
{
	message m;
	m.m1_p1 = procPtr;
	
	return _syscall(PM_PROC_NR, GETPROCTABLE , &m);
}


int sys_getqhead(struct qh *qPtr,u64_t *cpuFreqPtr)
{
	message m;
	m.m1_p1 = (char *)qPtr;
	m.m1_p2 = (char *)cpuFreqPtr;
	
	return _kernel_call(SYS_GETQHEAD, &m);
}
