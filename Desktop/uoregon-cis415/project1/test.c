#include "p1fxns.h" 
#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD 50
#define MAX_LINE 1024
void main(){
	int index = 0, result;
	char word[MAX_WORD];
	char lineBuf[MAX_LINE];
	while(p1getline(0, lineBuf, MAX_LINE)){
		while((result = p1getword(lineBuf, index, word)) != -1){
			index = result;
			printf(word);
			printf("\n");
			word[0] = '\0';
		}
		word[0] = '\0';
		index = 0;
	}
};
