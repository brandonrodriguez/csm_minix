/* !OSPROJ3!
 *	
 * do_getqhead
 * 
 * Request a copy of run_q_head
 * 
*/


#include <minix/callnr.h>	//Define for GETPROCTABLE (105)
#include <lib.h>			//Required for all lib c files
#include <minix/com.h>		//Def of _syscall
#include <minix/ipc.h> 		//Def of IPC/Message
#include <minix/pi.h>


int do_getqhead(struct proc * caller, message *m_ptr)
{
	printf("In Kernel Call\n");
	
	
	return 0;
}
