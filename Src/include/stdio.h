#ifndef _ORANGES_STDIO_H_
#define _ORANGES_STDIO_H_

#include "type.h"

/* 断言宏定义 */
#define ASSERT
#ifdef ASSERT
void assertion_failure(char *exp, char *file, char *base_file, int line);
#define assert(exp)  if (exp) ; \
        else assertion_failure(#exp, __FILE__, __BASE_FILE__, __LINE__)
#else
#define assert(exp)
#endif

/**在const.h中引入了extern(声明全局变量),又在global.c中通过宏方法除去(定义全局变量)*/
#define EXTERN extern

#define TRUE        1
#define FALSE       0

/* string */
#define STR_DEFAULT_LEN 1024

#define O_CREAT     1//0b0001
#define O_RDWR      2//0b0010
#define O_TRUNC     4//0b0100
#define FILE_FOLDER 8/*0b1000*/	

#define SEEK_SET    1
#define SEEK_CUR    2
#define SEEK_END    3

#define MAX_PATH    128

struct stat
{
    int st_dev;
    int st_ino;
    int st_mode;
    int st_rdev;
    int st_size;
};

struct time 
{
    u32 year;
    u32 month;
    u32 day;
    u32 hour;
    u32 minute;
    u32 second;
};


/* ---------*
    库函数 (给用户编程用)
*-----------*/

/* printf.c */
int printf(const char *fmt,...);
int printl(const char *fmt,...);

/* vsprintf.c */
int vsprintf(char *buf,const char *fmt,va_list args);
int sprintf(char *buf,const char *fmt,...);


/* lib/open.c */
int open(const char *,int);

/* lib/close.c */
int close(int);

/* lib/read.c */
int read(int ,void *,int );

/* lib/write.c */
int write(int ,const void *,int );

/* lib/lseek.c */
int lseek(int,int,int);

/*lib/ls.c*/
char* ls();

/*lib/pm.c*/
void showProcess();
void createProcess();
void killProcess(int pid);

/* lib/unlink.c */
int unlink(const char *);

/* lib/getpid.c */
int getpid();

/* lib/fork.c */
int fork();

/* lib/exit.c */
void exit(int status);

/* lib/wait.c */
int wait(int *status);

//lib/cd.c
int cd(const char * foldname);

//lib/ticks
int getTicks();

/* lib/exec.c */
int exec(const char *path);
int execl(const char *path,const char *arg,...);
int execv(const char *path,char *arg[]);

/* lib/stat.c */
int stat(const char *path,struct stat* buf);

//kernel/tool.c
void clear();
void mystrncpy(char* dest, char* src, int len);
void getorder(const char* rdbuf, char* order, int maxLen);
void respond(char *order, char *rdbuf, char* dir, int fd_stdin, int fd_stdout, int rdbufLen, int dirLen);

//kernel/showScreen
void CommandList();
void helpPM();
void helpGame();

#endif
