/*
 *	Jacob Dickisnon
 *	4/20/15
 *	This is my work
 */

#include "p1fxns.h"
#include "uspsList.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdbool.h>

volatile sig_atomic_t alrmflag = false;
int ulistIndex = 0;
void on_sigalrm(){
	ulistIndex++;
	alrmflag = true;
};

#define MAX_LINE 1024
#define MAX_WORD 512
int main(){
	int pid;
	int i = 0;
	int sig;
	int result;
	int id;
	
	char lineBuf[MAX_LINE];
	char fileBuf[MAX_LINE];

	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGSTOP);
	sigaddset(&set, SIGCONT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	signal(SIGALRM, on_sigalrm);
	
	UspsList *uList;
	uList = ul_create(); 
	if(uList == NULL){
		write(1, "failed to initialize\n", 21);
		return 0;
	}	

	
	while(p1getline(0, lineBuf, MAX_LINE) != 0){
		if((pid = fork()) < 0){
			write(1, "fork failed\n", 12);
			return 0;
		}
		if(!(ul_add(&uList, lineBuf))){
			write(1, "cannot creat add child to list\n", 31);
			return 0;
		}
		uList->first->u_pid = pid;
		if(pid == 0){
			uList->first->u_pid = pid;
			sigwait(&set, &sig);
			execvp(uList->first->program, uList->first->args);
		}
		i++;
	}
	ul_signal(uList, ulistIndex, SIGUSR1);
	alarm(1);
	
	for(;;){
		if(alrmflag){
			result = ul_status(uList, ulistIndex -1);
			if(result == 0){
				ul_signal(uList, ulistIndex - 1, SIGSTOP);
			}
			if(ulistIndex < i){
				ul_signal(uList, ulistIndex, SIGUSR1);
			}
			else{
				ul_signal(uList, ulistIndex, SIGCONT);
			}
			alrmflag = false;
			if(ul_done(uList)){
				break;
			}
			alarm(1);
		}
	}	
	
	
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	ul_destroy(uList);
	return 1;
};
