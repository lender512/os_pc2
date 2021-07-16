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
    char* worstId = NULL;

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
    char* bestId = NULL;

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

void compaction(struct linkedList *list) {
    
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