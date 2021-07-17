#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"


void userInput(int memorySize){
    if (memorySize == 0){
        printf("Please enter a valid number\n");
        exit(1);
    }
    else{
        printf("EXIRTO");
    }
}


int main(int argc, char *argv[]){
    char* size = argv[1];
    //userInput(atoi(firstArgument));
    char string [256];
    printf ("Insert your full address: ");
    gets (string);
    printf ("Your address is: %s\n",string);
    
    struct linkedList* head = initMemory(atoi(size));

    allocateF(&head,"P1",5);
    allocateF(&head,"P2",10);
    allocateF(&head,"P3",15);
    deallocate(head, "P1");

    // allocateF(&head,"P1",5);
    // allocateF(&head,"P2",25);
    // allocateF(&head,"P3",20);
    // printMemory(head);
    // deallocate(head, "P2");
    // printMemory(head);
    // allocateF(&head,"P4",10);
    // printMemory(head);
    // allocateF(&head,"P5",15);
    // printMemory(head);
    // deallocate(head, "P3");
    // printMemory(head);
    // allocateB(&head,"P6",16);
    printMemory(head);

    compaction(head);
    printMemory(head);

    return 0;
}
