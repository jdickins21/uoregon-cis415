/*
 *	Jacob Dickisnon
 *	4/20/15
 *	This is my work
 */


#ifndef _USPSLIST_H_
#define _USPSLIST_H_
#define MAX_LINE 1024
#define MAX_WORD 512

typedef struct uspsnode{
	struct uspsnode *next;
	char *program;
	char *args[MAX_LINE];
	int doneF;
	int u_pid;
}UspsNode;

typedef struct uspslist{
	struct uspsnode *first;
	struct uspsnode *last;
}UspsList;

/*creat a usps list*/
UspsList *ul_create(void);

/*add a node*/
int ul_add(UspsList **ul, char* line);

/*check status of process*/
int ul_status(UspsList *ul, int index);

/*change status of process*/
void ul_chngstatus(UspsList *ul, int index);

/*signal node*/
void ul_signal(UspsList *ul, int index, int signal);

/*check if all processes are done*/
int ul_done(UspsList *ul);

/*prints processes current status*/
int ul_getfileD(UspsList *ul, int index);

/*free node n*/
int destroy_node(UspsNode *n);

/*destroy usps list*/
void ul_destroy(UspsList *ul);

#endif
