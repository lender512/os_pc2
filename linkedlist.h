#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

struct linkedList {
    char* id;
    int base_adr;
    int top_adr;
    bool free;
    struct linkedList *next;
};

struct linkedList* initMemory(int size){
    struct linkedList* new_list = (struct linkedList*) malloc(sizeof(struct linkedList));
    new_list->id = (char*) malloc(sizeof(char) * (strlen("free") + 1));
    strcpy(new_list->id, "free");
    new_list->free = true;
    new_list->base_adr = 0;
    new_list->top_adr = size-1;
    new_list->next = NULL;
    return new_list;
}

void deallocate(struct linkedList *list, char* id) {
    struct linkedList *current = list;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            current->free = true;
            current->id = (char*) malloc(sizeof(char) * (strlen("free") + 1));
            strcpy(current->id, "free");
            break;
        }
        current = current->next;
    }
}


//first Fit

void allocateF(struct linkedList **list, char* id, int size) {

    struct linkedList *new_node = (struct linkedList*) malloc(sizeof(struct linkedList));
    new_node->id = (char*) malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(new_node->id, id);
    struct linkedList *current = *list;
    struct linkedList *prev = NULL;
    while (!(current->free && (current->top_adr - current->base_adr >= size))){
        prev = current;
        current = current->next;
        if (current == NULL){
            printf("Segmentation fault\n");
            return;
        }
    }

    new_node->base_adr = current->base_adr;
    new_node->top_adr = new_node->base_adr + size;
    new_node->free = false;
    // CHECK
    current->base_adr = current->base_adr + size + 1;
    if (prev != NULL){
        prev->next = new_node;
    }
    else{
        *list = new_node;
    }
    new_node->next = current;
}

void allocateW(struct linkedList **list, char* id, int size) {

    struct linkedList *new_node = (struct linkedList*) malloc(sizeof(struct linkedList));
    new_node->id = (char*) malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(new_node->id, id);


    struct linkedList* current = *list;
    struct linkedList *prev = NULL;
    int worstSize = 0;

    struct linkedList *worst = NULL;
    struct linkedList *prevWorst = NULL;

    while (current != NULL) {
        int currentSize = current->top_adr - current->base_adr;
        if (currentSize > worstSize && current->free && currentSize > size) {
            worstSize = currentSize;
            worst = current;
            prevWorst = prev;
        }
        prev = current;
        current = current->next;
    }
    
    if (worst == NULL){
        printf("Segmentation fault\n");
        return;
    }

    //printf("worst id %s size: %i\n", worst->id, worstSize);

    new_node->base_adr = worst->base_adr;
    new_node->top_adr = new_node->base_adr + size;
    new_node->free = false;
    // CHECK
    worst->base_adr = worst->base_adr + size + 1;
    if (prevWorst != NULL){
        prevWorst->next = new_node;
    }
    else{
        *list = new_node;
    }
    new_node->next = worst;
}

void allocateB(struct linkedList **list, char* id, int size) {

    struct linkedList *new_node = (struct linkedList*) malloc(sizeof(struct linkedList));
    new_node->id = (char*) malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(new_node->id, id);


    struct linkedList* current = *list;
    struct linkedList *prev = NULL;
    int bestSize = INT_MAX;

    struct linkedList *best = NULL;
    struct linkedList *prevBest = NULL;

    while (current != NULL) {
        int currentSize = current->top_adr - current->base_adr;
        if (currentSize < bestSize && current->free && currentSize > size) {
            bestSize = currentSize;
            best = current;
            prevBest = prev;
        }
        prev = current;
        current = current->next;
    }
    
    //printf("worst id %s size: %i\n", worst->id, worstSize);

    if (best == NULL){
        printf("Segmentation fault\n");
        return;
    }

    new_node->base_adr = best->base_adr;
    new_node->top_adr = new_node->base_adr + size;
    new_node->free = false;
    // CHECK
    best->base_adr = best->base_adr + size + 1;
    if (prevBest != NULL){
        prevBest->next = new_node;
    }
    else{
        *list = new_node;
    }
    new_node->next = best;
}

void compaction(struct linkedList* list){
    struct linkedList* current = list;
    struct linkedList* last_allocated = list;
    bool found_free = false;
    while (current != NULL) {
        if (current->free) {
            found_free = true;
        }
        if (!found_free) {
            last_allocated = current;
        }
        if (found_free && !current->free) {
            if (last_allocated->free) {
                printf("current: %s\n", current->id);
                swapLinkedList(&list, last_allocated, current);
            } else {
                swapLinkedList(&list, last_allocated->next, current);
            
            }
        }
        current = current->next;
    }
}

// swap Linked List nodes

struct linkedList* findPrevLinkedList(struct linkedList *list, struct linkedList* find){
    struct linkedList* prev = list;
    while (prev != NULL) {
        if (prev->next == find) {
            break;
        }
        prev = prev->next;
    }
    return prev;
}


void swapLinkedList(struct linkedList** list,struct linkedList *node1, struct linkedList *node2){
    if (node1 == node2){
        return;
    }
    
    struct linkedList *prev1 = findPrevLinkedList(list, node1);
    struct linkedList *prev2 = findPrevLinkedList(list, node2);
    
    if(node1 != NULL && node2 != NULL) {  
        if (prev1 != NULL){
            prev1->next = node2;
        } else {
            *list = node1;
        }

        if (prev2 != NULL){
            prev2->next = node1;
        } else {
            *list = node2;
        }

        struct linkedList *temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;
    }

    // struct linkedList *tempRescue = node1->next;

    // prev1->next = node2;

    // if (prev2 == node1){
    //     prev2->next = node2->next;
    // }
    // else{
    //     prev2->next = node1; //next
    // }

    // struct linkedList *temp = node2->next;

    // if (node2 == tempRescue){
    //     node2->next = node1;
    // }
    // else{
    //     node2->next = node1->next; //next
    //     node1->next = temp;
    // }

    struct linkedList *new_prev1 = findPrevLinkedList(list, node1);
    struct linkedList *new_prev2 = findPrevLinkedList(list, node2);



    int size1 = node1->top_adr - node1->base_adr; 
    int size2 = node2->top_adr - node2->base_adr;

    if (new_prev1 != NULL && new_prev2 != NULL) {
        node2->base_adr = new_prev2->top_adr + 1;
        node2->top_adr = node2->base_adr + size2;
        
        node1->base_adr = new_prev1->top_adr + 1;
        node1->top_adr = node1->base_adr + size1;
    }
}


void printMemory(struct linkedList *list) {
    struct linkedList *current = list;
    while (current != NULL) {
        printf("Addresses [%i:%i] ",current->base_adr, current->top_adr);
        current->free ? printf("Unused\n") : printf("Process %s\n", current->id);
        current = current->next;
    }
    printf("\n");
}