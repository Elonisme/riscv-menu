#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define FONTSIZE 10
int PrintMenuOS()
{
  int i, j;
  char data_M[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "  *    *  ",
        " ***  *** ",
        " * *  * * ",
        " * *  * * ",
        " *  **  * ",
        " *      * ",
        " *      * ",
        " *      * ",
        "          "
    };
    char data_e[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "    **    ",
        "   *  *   ",
        "  *    *  ",
        "  ******  ",
        "  *       ",
        "   *      ",
        "    ***   ",
        "          "
    };
    char data_n[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "    **    ",
        "   *  *   ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "          "
    };
    char data_u[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "          ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "  *    *  ",
        "   *  **  ",
        "    **  * ",
        "          "
    };
    char data_O[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "   ****   ",
        "  *    *  ",
        " *      * ",
        " *      * ",
        " *      * ",
        " *      * ",
        "  *    *  ",
        "   ****   ",
        "          "
    };
    char data_S[FONTSIZE][FONTSIZE] =
    {
        "          ",
        "    ****  ",
        "   **     ",
        "  **      ",
        "   ***    ",
        "     **   ",
        "      **  ",
        "     **   ",
        "  ****    ",
        "          "
    };

    for(i=0; i<FONTSIZE; i++)
    {
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_M[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_e[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_n[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_u[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_O[i][j]);
        }
        for(j=0; j<FONTSIZE; j++)
        {
            printf("%c", data_S[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int CWrite(void){
  char s[]="hello, world\n";
	write(1,s,13);
	return 0;
  return 0;
}

int WriteAsm(void){
      char s[] = "hello, world\n";

    __asm__ volatile(
		    "li a2, 13\n"
		    "li a0, 1\n"
		    "mv a1, %[str]\n"
	    	    "li a7, 64\n"
		    "ecall \n"
		    :
		    : [str] "r" (s)
    );

    return 0;
}

int Quit(int argc, char *argv[])
{
    /* add XXX clean ops */
}

int Time(int argc, char *argv[])
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == 0) {
        time_t current_time = tv.tv_sec;
        struct tm *tm_info = localtime(&current_time);

        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y:%m:%d %H:%M:%S", tm_info);
        printf("Current time: %s\n", buffer);
    } else {
        perror("gettimeofday");
    }
    return 0;
}

int TimeAsm(int argc, char *argv[])
{
  time_t tt;
  struct timeval tv;
  struct tm *t;

  #if 0
      gettimeofday(&tv, NULL);
  #else
  asm volatile(
    "li a7, 169\n\t"
    "li a0, 0\n\t"
    "ecall\n\t"
    "mv %0, a0\n\t"
    : "=r" (tv.tv_sec)
   );
  #endif

  tt = tv.tv_sec;
  t = localtime(&tt);

  printf("time:%d:%d:%d:%d:%d:%d\n",t->tm_year+1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
  return 0;
}

int ForkProcess(int argc, char *argv[]){
  int pid;
  pid = fork();
  if(pid < 0){
    fprintf(stderr, "Fork Failed!");
    exit(-1);
  }
  else if (pid == 0){
    printf("This is Child Process!\n");
  }
  else {
    printf("This is Parent Process!\n");
    wait(NULL);
    printf("Child Complete!\n");
  }

  return 0;
}


int Exec(int argc, char *argv[])
{
	int pid;
	/* fork another process */
	pid = fork();
	if (pid < 0)
	{
		/* error occurred */
		fprintf(stderr,"Fork Failed!");
		exit(-1);
	}
	else if (pid == 0)
	{
		/*	 child process 	*/
    	printf("This is Child Process!\n");
		execlp("/hello","hello",NULL);
	}
	else
	{
		/* 	parent process	 */
    	printf("This is Parent Process!\n");
		/* parent will wait for the child to complete*/
		wait(NULL);
		printf("Child Complete!\n");
	}
}


int main()
{
    PrintMenuOS();
    SetPrompt("MenuOS>>");
    MenuConfig("version","MenuOs V2.0(Based on Linux 5.19.16)",NULL);
    MenuConfig("quit","Quit from MenuOS",Quit);
    MenuConfig("time","Show System Time",Time);
    MenuConfig("time-asm","Show System Time(asm)",TimeAsm);
    MenuConfig("write", "Write hello world", CWrite);
    MenuConfig("write-asm", "Write hello world(asm)", WriteAsm);
    MenuConfig("fork-new", "fork new process", ForkProcess);
    MenuConfig("exec", "execve new process", Exec);
    ExecuteMenu();
}
