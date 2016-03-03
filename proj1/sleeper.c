/*
 * sleeper.c
 *
 * Created by Daniel Johnson
 *
 * This program is designed to report, sleep for 10 seconds and report again
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	// switch on the number of arguments
    switch(argc)
    {
        // if one argument is used attempt to use as input file
        case 2:
        break;
        // else display intended usage
        default:
        printf("Usage: %s seconds_to_sleep\n", argv[0]);
	    return -1;
    }
    int t = atoi(argv[1]);
    pid_t pid = getpid();
    printf("process %d going to sleep mode for %d seconds\n", pid, t);

    sleep(t);

    printf("done sleeping\n");

    return 0;

}