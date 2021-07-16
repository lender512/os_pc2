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
    
    
    struct linkedList* head = initLinkedList("free",atoi(size));
    insertLinkedList(&head,"holias",20);
    insertLinkedList(&head,"porremover",20);
    insertLinkedList(&head,"jasjasj",20);
    printLinkedList(head);
    removeLinkedList(head, "porremover");
    printLinkedList(head);
    return 0;
}
