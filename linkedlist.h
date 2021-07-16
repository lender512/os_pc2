#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

void printMemory(struct linkedList *list) {
    struct linkedList *current = list;
    while (current != NULL) {
        printf("id: %s, base address: %i, top address: %i", current->id, current->base_adr, current->top_adr);
        current->free ? printf(" FREE\n") : printf(" ALLOCATED\n");
        current = current->next;
    }
    printf("\n");
}