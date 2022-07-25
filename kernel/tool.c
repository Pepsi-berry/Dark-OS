/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							tool.c
放置了自己完成的小工具函数
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
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

/*清屏*/
void clear()
{
	for(int i = 0; i < 25 ;i++)
		printf("\n");
}

/*拷贝指定数量字符串*/
void mystrncpy(char* dest, char* src, int len)
{

	char* temp = dest;
	int i = 0;
	while (i++ < len && (*temp++ = *src++) != '\0');

	if (*(temp) != '\0') {
		*temp = '\0';
	}
}

/*获取指令*/
void getorder(const char* rdbuf, char* order, int maxLen)
{
	for(int i = 0; i < maxLen; i++)
		order[i] = '\0';
	for(int i = 0; rdbuf[i] != ' ' && i < maxLen; i++)
		order[i] = rdbuf[i];
}
/*获取指令尾*/
char* getcontent(char* rdbuf, char* nullstd, int orderLen, int rdbufLen)
{	/*存在一个空格*/
	orderLen++;
	if(orderLen >= rdbufLen)	
		return nullstd;

	return rdbuf + orderLen;
}
/*获取文件类型*/
int gettype(int fd)
{
	int returnnum = 1;

	struct inode * new_inode = get_inode(root_inode->i_dev, fd);
	if(new_inode->i_mode != I_REGULAR)
		returnnum = 0;
	printl("%d\n", new_inode->i_mode);
	put_inode(new_inode);

	return returnnum;
}
/*获取文件大小*/
int getsize(int fd)
{
	int returnnum = 0;

	struct inode * new_inode = get_inode(root_inode->i_dev, fd);
	returnnum = new_inode->i_size;
	put_inode(new_inode);

	return returnnum;
}
/*处理打开文件*/
void openfile(int fd, int fd_stdin, char* filename)
{

	fd = open(filename, O_RDWR);
	int rdbufLen = 0;
	char rdbuf[128];
		
	//获取旧文件大小
	//const int filesize_old = getsize(fd);
	printf("%s:\n", filename);	
	//for(int gotsize = 0; gotsize < filesize_old; gotsize += 512)
	//{
		char bufr[512] = {};
		int getLen;
		//读原有内容
		getLen = read(fd, bufr, 512);
		bufr[getLen] = 0;
		//打印原有内容
		printf("%s\n", bufr);
	//}
	
	close(fd);
	fd = open(filename, O_RDWR);
	
	while(1)
	{
		//输入新内容
		printf("input %s(use \"exit\" to finish):", filename);
		rdbufLen = read(fd_stdin, rdbuf, 80);
		rdbuf[rdbufLen] = 0;
		if(!strcmp(rdbuf, "exit"))
			break;
		//写入新内容
		write(fd, rdbuf, rdbufLen);
	}

	close(fd);
	fd = open(filename, O_RDWR);
	
	//获取新文件大小
	//const int filesize_new = getsize(fd);
	//printf("%d\n", filesize_new);
	printf("%s:\n", filename);	
	//for(int gotsize = 0; gotsize < filesize_new; gotsize += 512)
	//{
		//char bufr[512] = {};
		//int getLen;
		//读新内容
		getLen = read(fd, bufr, 512);
		bufr[getLen] = 0;
		//打印新内容
		printf("%s\n", bufr);
	//}

	close(fd);
}
void changedir(char* dir, char* content, int dirLen)
{
	if(!strcmp(content, ".."))
	{
		dir[dirLen - 1] = 0;
		for(int i = dirLen - 1; dir[i] != '/' && i >= 0; i--)
			dir[i] = 0;
		return;
	}
	int i = 0;
	for(i = 0; content[i] != 0; i++)
		dir[dirLen + i] = content[i];
	dir[dirLen + i++] = '/';
	dir[dirLen + i] = 0;
}
void doecho(char * centent)
{
	printf("write here shun shun !\n");
}

void processManager(int fd_stdin, int fd_stdout)
{
	clear();
	helpPM();

	int rd_len = 0;
	char rdbuf[64];
	char order[7 + 1];
	char* nullstd = "NULL";
	char* content = "NULL";
	while(1)
	{
		printf("@RASPBERRYOS ~ process-manager: $ ");
		rd_len = read(fd_stdin, rdbuf, 64);
		rdbuf[rd_len] = 0;

		getorder(rdbuf, order, 7);
		if(!strcmp(order, "help"))
		{
			clear();
			helpPM();
		}
		else if (0 == strcmp(order, "clear"))
			clear();
		else if (0 == strcmp(order, "quit"))
			break;
		else if(0 == strcmp(order, "ps"))
		{
			showProcess();
		}
		else if(0 == strcmp(order, "create"))
		{
			createProcess();
		}
		else if(0 == strcmp(order, "kill"))
		{
			char* content = getcontent(rdbuf, nullstd, 4, rd_len);
			killProcess((int)(content[0] - '0'));
		}
	}
}

/*根据指令作出回应*/
void respond(char *order, char *rdbuf, char* dir, int fd_stdin, int fd_stdout, int rdbufLen, int dirLen)
{
	char* content = "NULL";
	char* nullstd = "NULL";
	if (!strcmp(order, "help"))
	{
		clear();
		CommandList();
	}
	else if (!strcmp(order, "clear"))
	{
		clear();
	}
	else if (!strcmp(order, "ls"))
	{
		printf("list in now dir\n");
		printf("-----------------------------\n");
		printf("*\n");
		printf("%s", ls());
		printf("*\n");
		printf("-----------------------------\n");
	}
	else if(!strcmp(order, "touch"))
	{
		content = getcontent(rdbuf, nullstd, 5,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a file name\n");
		else
		{
			int fd = open(content, O_CREAT | O_RDWR);
			if(-1 != fd && -2 != fd)
				close(fd);
			if(-2 == fd)
				printf("{FS} file exists: %s\n",content);
		}
	}
	else if(!strcmp(order, "mdir"))
	{
		content = getcontent(rdbuf, nullstd, 4,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a folder name\n");
		else
		{
			int fd = open(content, O_CREAT | O_RDWR | FILE_FOLDER);
			if(-1 != fd && -2 != fd)
				close(fd);
			if(-2 == fd)
				printf("{FS} file exists: %s\n",content);
		}
	}
	else if(!strcmp(order, "cd"))
	{
		content = getcontent(rdbuf, nullstd, 2,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a folder name or \"..\"\n");
		else
		{
			int ans = cd(content);
			if(0 == ans)
				changedir(dir, content, dirLen);
			else if(-1 == ans)
				printf("Already in the root file\n");
			else
				printf("NO folder found to enter\n");
			
		}
	}
	else if(!strcmp(order, "rm"))
	{
		content = getcontent(rdbuf, nullstd, 2,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a file or folder name\n");
		else
		{
			if(!unlink(content))
				printf("\"%s\" deleted successfully\n", content);
			else
				printf("\"%s\" delete failed\n", content);
		}
	}
	else if(!strcmp(order, "open"))
	{
		content = getcontent(rdbuf, nullstd, 4,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a file name\n");
		else
		{
			int fd = open(content, O_RDWR);
			if(-1 == fd)
				printf("No corresponding file found\n");
			else
			{
				close(fd);
				//if(gettype(fd))
					openfile(fd, fd_stdin, content);
				//else
					//printf("can't open this file\n");
			}
		}
	}
	else if(!strcmp(order, "echo"))
	{
		content = getcontent(rdbuf, nullstd, 4,rdbufLen);
		if(!strcmp(content, nullstd))
			printf("Please enter a echo order\n");
		else
		{
			doecho(content);
		}
	}
	else if(0 == strcmp(order, "pm"))
	{
		processManager(fd_stdin, fd_stdout);
	}
	else
	{
		printf("      #                 Input [help] for more information.               #\n");
	}
}
