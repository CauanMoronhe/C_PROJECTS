#include <stdio.h>
#include <stdlib.h>

typedef struct nodeMusic{
    char music; // data to be stored
    struct nodeMusic *next; // points to the next node in the list
    struct nodeMusic *back; // points to previous node in the list
}nodeMusic;

typedef struct musicList{
    struct nodeMusic *begin; // will store the first node in the list
    struct nodeMusic *current; // tracks the music currently playing
    struct nodeMusic *end; // will save the last node in the list
}musicList;



int main(){



    return 0;
}
