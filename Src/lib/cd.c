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
 *                                cd
 *****************************************************************************/
/**
 * in new dir
 * 
 * @param pathname  open folder
 * 
 * @return Zero if successful, otherwise -1.
 *****************************************************************************/
int cd(const char * foldname)
{
	MESSAGE msg;
	msg.type   = CD;

	msg.PATHNAME	= (void*)foldname;
	msg.NAME_LEN	= strlen(foldname);

	send_recv(BOTH, TASK_FS, &msg);

	return msg.RETVAL;
}
