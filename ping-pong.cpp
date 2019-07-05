#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
using namespace std;

/**
 * @brief Handler for SIGUSR1 signal
 * @param sig - SIGUSR1
 */
void sigHandler(int sig);
/**
 * @brief Handler for SIGINT signal
 * @param sig - SIGINT
 */
void exitHandler(int sig);
/**
	@brief flag to find out if a SIGUSR1 been received
 */
bool c = false;
/**
	@brief flag to find out if a SIGINT been received
 */
bool a = false;
/**
 * @brief Program entry point
 */
int main(int argc,char ** argv)
{
	int childPid;
	signal(SIGUSR1,sigHandler);
	signal(SIGINT,exitHandler);
	/**
	 * Here is fork. First block is son, second is father
	 */
	if (0==(childPid=fork()))
	{	///son
		while (!a)
		{
			if (!c) pause();
			c = false;
			if (!a) cout<<getpid()<<": Pong\n";
			if (!a) sleep(1);
			if (!a) kill(getppid(),SIGUSR1);
		}
#ifdef DEBUG 
		cout<<getpid()<<" terminated\n";
#endif
		return 0;
	}
	else {	///father
		c = true;
		while (!a)
		{
			if (!c) pause();
			c = false;
			if (!a) cout<<getpid()<<": Ping\n";
			if (!a) sleep(1);
			if (!a) kill(childPid,SIGUSR1);
		}
		kill(childPid,SIGINT);
		wait(&childPid);
#ifdef DEBUG
		cout<<getpid()<<" terminated\n";
#endif
		return 0;
	}
}

void sigHandler(int sig)
{
	signal(SIGUSR1,sigHandler);
	c = true;
	
}

void exitHandler(int sig)
{
	signal(SIGUSR1,SIG_IGN);
	signal(SIGALRM,SIG_IGN);
	a=true;
}
