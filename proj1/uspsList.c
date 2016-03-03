/*
 *	Jacob Dickisnon
 *	4/20/15
 *	This is my work
 */


#include "uspsList.h"
#include "p1fxns.h"
#include <stdlib.h>
#include <unistd.h>

/*creat a usps list*/
UspsList *ul_create(void){
	UspsList *u;

	if((u = (UspsList *)malloc(sizeof(UspsList))) != NULL){
		u->first = NULL;
		u->last = NULL;
	}
	return u;
}

/*add a node*/
int ul_add(UspsList **ul, char line[MAX_LINE]){
	UspsList *u;
	UspsNode *n;
	int index;
	int i = 0;
	char word[MAX_WORD];
	u = *ul;
	if ((n = (UspsNode *)malloc(sizeof(UspsNode))) == NULL)
		return 0;
	index = p1getword(line, index, word);
	n->program = p1strdup(word);
	n->args[0] = p1strdup(word);
   	i++;
    	while((index = p1getword(line, index, word)) != -1){
        	n->args[i] = p1strdup(word);
        	i++;
    	}
	n->doneF = 0;
	n->next = u->first;
	u->first = n;
	if (!(u->last))
		u->last = n;
	return 1;

}

/*check status of process*/
int ul_status(UspsList *ul, int index){
	int status;
	int i;
	UspsList *u;
	UspsNode *cur;

	u = ul;
	cur = u->first;
	for(i = 0; i < index; i++){
		cur = cur->next;
		if(cur == NULL){
			cur = u->first;
		}
		if(cur->doneF > 0){
			cur = cur->next;
		}
	}	

	return waitpid(cur->u_pid, &status, WNOHANG);
}

/*change status of process*/
void ul_chngstatus(UspsList *ul, int index){
	UspsList *u;
	UspsNode *cur;
	int i;

	u = ul;
	cur = u->first;

	for(i = 0; i < index; i++){
		cur = cur->next;
		if(cur == NULL){
			cur = u->first;
		}
	}
	
	cur->doneF++;
}

/*signal node*/
void ul_signal(UspsList *ul, int index, int signal){
	UspsList *u;
	UspsNode *cur;
	UspsNode *temp;
	int i;

	u = ul;
	cur = u->first;

	for(i = 0; i < index; i++){
		cur = cur->next;
		if(cur == NULL){
			cur = u->first;
		}
	}
	kill(cur->u_pid, signal);
	
}

/*prints processes current status*/
int ul_getfileD(UspsList *ul, int index){
	UspsList *u;
	UspsNode *cur;
	int i;

	u = ul;
	cur = u->first;
	for(i = 0; i < index; i++){
		cur = cur->next;
		if(cur == NULL){
			cur = u->first;
		}
	}
	return open("/proc/cur->u_pid/status", "r");
	
	
}

/*check if all processes are done*/
int ul_done(UspsList *ul){
	UspsList *u;
	UspsNode *cur;
	int status;
	int result = 0;
	u = ul;
	cur = u->first;

	while(cur != NULL){
		result = waitpid(cur->u_pid, &status, WNOHANG);
		if(result == 0){
			return 0;
		}
		cur = cur->next;
	}
	return 1;
	
}

/*free node n*/
int destroy_node(UspsNode *n){
	int i;
	
	if(n->program != NULL){
		free(n->program);
	}
	for(i = 0; i < MAX_LINE; i++){
		if(n->args[i] != NULL){
			free(n->args[i]);
		}
	}
	return 1;
}

/*destroy usps list*/
void ul_destroy(UspsList *ul){
	UspsNode *n;

	n = ul->first;
	while(n != NULL){
		UspsNode *r = n->next;
		destroy_node(n);	
		free(n);
		n = r;
	}
	if(ul != NULL){
		free(ul);
	}
}

