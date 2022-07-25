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
 *                                do_ls
 *****************************************************************************/
/**
 * ls
 * 
 * @return 0
 *****************************************************************************/
void* do_ls(int fd_stdout)
{
	int i, j;

	int listLen = 0;
	char list[512] = {};
	char filename[MAX_PATH];
	memset(filename, 0, MAX_FILENAME_LEN);
	struct inode * dir_inode = root_inode;
	struct inode * file_inode;
	
	
	int dir_blk0_nr = dir_inode->i_start_sect;
	int nr_dir_blks = (dir_inode->i_size + SECTOR_SIZE - 1) / SECTOR_SIZE;
	int nr_dir_entries = dir_inode->i_size / DIR_ENTRY_SIZE; 
	int m = 0;
	int nameLen = 0;
	
	struct dir_entry * pde;

	for (i = 0; i < nr_dir_blks; i++) 
	{
		RD_SECT(dir_inode->i_dev, dir_blk0_nr + i);

		pde = (struct dir_entry *)fsbuf;
		
		for (j = 0; j < SECTOR_SIZE / DIR_ENTRY_SIZE; j++,pde++) 
		{
			for(int i = 0; pde->name[i] != 0; i++)
				list[listLen++] = pde->name[i];
			list[listLen++] = '\n';

			if (++m > nr_dir_entries)
				break;
		}
		if (m > nr_dir_entries) 
			break;
	}
	
	list[listLen] = 0;
	phys_copy((void*)va2la(fs_msg.source, fs_msg.PATHNAME),
		  (void*)va2la(TASK_FS, list),
		  listLen + 1);
	return 0;
	
}
