//
//  mentry.c
//  
//
//  Created by Jacob Dickinson on 4/7/15.
///Users/jake/Desktop/uoregon-cis415/Project0Start/mentry.h
//

#include <stdlib.h>
#include <string.h>
#include "mentry.h"


/* me_get returns the next file entry, or NULL if end of file */
MEntry *me_get(FILE *fd){
    //printf("start\n");
    MEntry *entry = malloc(sizeof*(entry));
    //printf("malloc\n");
    char lineOne[100], lineTwo[100], lineThree[100];
    fgets(lineOne, 100, fd);
    
    //check if at end
    if(feof(fd)){
        free(entry);
        return NULL;
    }
    
    //printf("Line one: %s", lineOne);
    fgets(lineTwo, 100, fd);
    //printf("Line two: %s", lineTwo);
    fgets(lineThree, 100, fd);
    //printf("Line three: %s", lineThree);
    //copy last name
    char *p;
    entry->surname = strdup(lineOne);
    if((p = strrchr(entry->surname, ','))){
        *p = 0;
    }    //printf("surname: %s\n", entry->surname);

    //hpuse number
    entry->house_number = atoi(lineTwo);
    //printf("house number: %d \n", entry->house_number);
    
    //get last five digits of last address line for zip
    entry->zipcode = strrchr(lineThree, ' ');
    entry->zipcode += 1;
    //printf("zip: %s \n", entry->zipcode);

    strcat(lineOne, lineTwo);
    strcat(lineOne, lineThree);
    entry->full_address = strdup(lineOne);
    //printf("full address: %s \n", entry->full_address);
    
    //return entire struct
    return entry;
}

/* me_hash computes a hash of the MEntry, mod size */
unsigned long me_hash(MEntry *me, unsigned long size);

/*me_print prints the full address on fd */
void me_print(MEntry *me, FILE *fd){
    fprintf(fd, "%s", me->full_address);
}

/* me_compare compares two mail entries, returning <0, 0, >0 if
 * me1<me2, me1==me2, me1>me2
 */
int me_compare(MEntry *me1, MEntry *me2){
    //int to return
    int nameInt = 0, houseInt = 0, zipInt = 0;
    
    //check last name
    nameInt = strcmp(me1->surname, me2->surname);
    
    //check house number
    houseInt = me1->house_number -  me2->house_number;
    
    //check zip
    zipInt = strcmp(me1->zipcode, me2->zipcode);
    
    // return tatal
    return (nameInt + houseInt + zipInt);
}

/* me_destroy destroys the mail entry */
void me_destroy(MEntry *me){
    if(me->surname != NULL)
        free(me->surname);
    if(me->zipcode != NULL)
        free(me->zipcode);
    if(me->full_address != NULL)
        free(me->full_address);
    free(me);
}
