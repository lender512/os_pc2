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
    
    
    struct linkedList* head = initMemory(atoi(size));
    allocateF(&head,"holias",20);
    allocateF(&head,"porremover",20);
    allocateF(&head,"jasjasj",20);
    printMemory(head);
    deallocate(head, "porremover");
    printMemory(head);
    allocateF(&head,"jasjasj",10);
    printMemory(head);
    allocateF(&head,"jasjasj",15);
    printMemory(head);

    allocateW(&head,"ajsdjasd",1);
    return 0;
}
