/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							showScreen.c
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


/*所有指令 & help窗口*/
void CommandList()
{
	printf("      ====================================================================\n");
	printf("      #                           Welcome  to                            #\n");
	printf("      #                           RASPBERRYOS                            #\n");
	printf("      #                         * *  *****  * *                          #\n");
	printf("      #                           *  *****  *                            #\n");
    printf("      #                           ***********                            #\n");
	printf("      #                         **   *   *   **                          #\n");
	printf("      #                      **        *        **                       #\n");
	printf("      #                     *     *         *     *                      #\n");
	printf("      #                     *          *       *  *                      #\n");
	printf("      #                       *      *    *     *                        #\n");
	printf("      #                          *    *  *   *                           #\n");
	printf("      #                             *******                              #\n");
	printf("      #                          [COMMAND LIST]                          #\n");
	printf("      #            $ help          --- show the command list             #\n");
	printf("      #            $ clear         --- clear the cmd                     #\n");
	printf("      #            $ touch [name]  --- make new file                     #\n");
	printf("      #            $ mdir [name]   --- make new folder                   #\n");
	printf("      #            $ cd [folder]   --- enter a folder                    #\n");
	printf("      #            $ ls            --- show all files in current folder  #\n");
	printf("      #            $ proce         --- process manager                   #\n");
	printf("      #                                                                  #\n");
	printf("      #            You can use [CTRL + F1/F2/F3] to switch consoles      #\n");
	printf("      #                                                                  #\n");
	printf("      ====================================================================\n");


	//printf("\n\n");
}

void helpPM()
{
	printf("      ====================================================================\n");
	printf("      #                     Welcome  to  RASPBERRYOS                     #\n");
	printf("      #                         * *  *****  * *                          #\n");
	printf("      #                        *****************                         #\n");
    printf("      #                           ***********                            #\n");
	printf("      #                         **   *   *   **                          #\n");
	printf("      #                      **        *        **                       #\n");
	printf("      #                     *     *         *     *                      #\n");
	printf("      #                     *                     *                      #\n");
	printf("      #                      **      *    *     **                       #\n");
	printf("      #                       **               **                        #\n");
	printf("      #                          **   *  *  **                           #\n");
	printf("      #                              *****                               #\n");
	printf("      #             [COMMAND]                 [FUNCTION]                 #\n");
	printf("      #           $ ps           |     show all process                  #\n");
	printf("      #           $ kill [id]    |     kill a process                    #\n");
	printf("      #           $ create       |     restart a process                 #\n");
	printf("      #           $ quit         |     quit process management system    #\n");
	printf("      #           $ help         |     show command list of this system  #\n");
	printf("      #           $ clear        |     clear the cmd                     #\n");
	printf("      #            You can use [CTRL + F1/F2/F3] to switch consoles      #\n");
	printf("      ====================================================================\n");


	printf("");
}

void helpGame()
{
    printf("      ====================================================================\n");
	printf("      #                           Welcome  to                            #\n");
	printf("      #                           RASPBERRYOS                            #\n");
	printf("      #                         * *  *****  * *                          #\n");
	printf("      #                        *****************                         #\n");
    printf("      #                           ***********                            #\n");
	printf("      #                         **   *   *   **                          #\n");
	printf("      #                       **               **                        #\n");
	printf("      #                      **        *        **                       #\n");
	printf("      #                     *     *         *     *                      #\n");
	printf("      #                     *                     *                      #\n");
	printf("      #                      **      *    *     **                       #\n");
	printf("      #                       **               **                        #\n");
	printf("      #                          **   *  *  **                           #\n");
	printf("      #                            *       *                             #\n");
	printf("      #                              *****                               #\n");
	printf("      #                          [COMMAND LIST]                          #\n");
	printf("      #            $ echo help     --- show the command list             #\n");
	printf("      #            $ echo clear    --- clear the cmd                     #\n");
	printf("      #            $ echo help     --- show the game guide in detail     #\n");
	printf("      #            $ echo [-option]--- play the built-in game            #\n");
	printf("      #                                                                  #\n");
	printf("      #            You can use [CTRL + F1/F2/F3] to switch consoles      #\n");
	printf("      #                                                                  #\n");
	printf("      ====================================================================\n");


	//printf("\n\n");

}




