#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

/*****************************************************************************
 *                                pm
 *****************************************************************************/
/**               basic function of process manager
 *****************************************************************************/

void showProcess()
{
	int i;
	printf("===============================================================================\n");
	printf("    ProcessID    *    ProcessName    *    ProcessPriority    *    If Running   \n");
	//进程号，进程名，优先级，是否在运行
	printf("-------------------------------------------------------------------------------\n");
	for (i = 0; i < NR_TASKS + NR_PROCS; i++)//逐个遍历
	{
        if(proc_table[i].p_flags != FREE_SLOT)
        {
    		printf("        %d", proc_table[i].pid);
    		printf("                 %5s", proc_table[i].name);
    		printf("                   %2d", proc_table[i].priority);
    		if (proc_table[i].p_flags == 0)
	    		printf("                   no\n");
	    	else
		    	printf("                   yes\n");
		    //printf("        %d                 %s                   %d                   yes\n", 
            //proc_table[i].pid, proc_table[i].name, proc_table[i].priority);
        }
	}
	printf("===============================================================================\n\n");
}

void killProcess()
{
	;
}

void createProcess()
{
	int pid = fork();

	if (pid != 0)
    {
        printf("[parent is running, child pid:%d\n]", pid);
        proc_table[pid].pid = pid;
		int s = 0;
		int child = wait(&s);
        printf("[Child %d exited with status: %d.\n]", child, s);
    }
    else 
    {
        pid = getpid();
        printf("[child is running, pid:%d]\n", pid);
		exit(666);
        //assert(0);
    }

	return;

}

