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
 *                                ls
 *****************************************************************************/
/**
 * in new dir
 * 
 * @param Show all file or folder in now dir
 * 
 * @return Zero if successful, otherwise -1.
 *****************************************************************************/
char* ls(int fd_stdout)
{
	MESSAGE msg;
	msg.type   = LSEEK;
	//msg.RETVAL = fd_stdout;
	send_recv(BOTH, TASK_FS, &msg);

	return (char*)msg.PATHNAME;
}
