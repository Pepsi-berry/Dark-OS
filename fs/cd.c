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
#include "keyboard.h"
#include "proto.h"

/*****************************************************************************
 *                                do_cd
 *****************************************************************************/
/**
 * Open a fold or back
 * 
 * @return 0(G) or -1(B) or -2(B)
 *****************************************************************************/
int do_cd()
{
	struct inode * old_inode = root_inode;
	struct inode * new_inode;
	int new_inodenum = 0;
	int returnnum = 0;

	char pathname[MAX_PATH];

	/* get parameters from the message */
	int name_len = fs_msg.NAME_LEN;	/* length of filename */
	int src = fs_msg.source;	/* caller proc nr. */
	assert(name_len < MAX_PATH);
	phys_copy((void*)va2la(TASK_FS, pathname),
		  (void*)va2la(src, fs_msg.PATHNAME),
		  name_len);
	pathname[name_len] = 0;

	/*如果是返回文件*/
	if(0 == strcmp(pathname,".."))
	{
		/*如果为根文件*/
		if(old_inode->i_num == 1)
		{
			//printl("Already in the root file\n");
			returnnum = -1;
		}
		else
		{
			//printl("%d\n", old_inode->i_father);
			if(0 == old_inode->i_father)
				old_inode->i_father = 1;
			new_inode = get_inode(root_inode->i_dev, old_inode->i_father);
			put_inode(old_inode);
			root_inode = new_inode;
		}
	}
	else
	{
		
		new_inodenum = search_file(pathname);
		printl("%d\n", new_inodenum);
		if(new_inodenum)
		{
			new_inode = get_inode(root_inode->i_dev, new_inodenum);
		}
		/*发现文件夹且为文件夹*/		
		if(new_inodenum && (new_inode->i_mode == I_DIRECTORY))
		{
			root_inode = new_inode;
			//printl("%d\n", root_inode->i_num);
		}
		else
		{
			//printl("NO folder found to enter\n");
			returnnum = -2;
		}
	}

	return returnnum;
}


