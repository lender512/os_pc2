#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct linkedList {
    char* id;
    int base_adr;
    int top_adr;
    bool free;
    struct linkedList *next;
};

void removeLinkedList(struct linkedList *list, char* id) {
    struct linkedList *current = list;
    struct linkedList *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->id, id) == 0) {
            if (prev == NULL) {
                list = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->id);
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}


//first Fit
void insertLinkedList(struct linkedList **list, char* id, int size) {
    struct linkedList *new_node = (struct linkedList*) malloc(sizeof(struct linkedList));
    new_node->id = (char*) malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(new_node->id, id);
    struct linkedList *current = *list;
    while (!current->free && (current->top_adr - current->base_adr > size)){
        current = current->next;
    }
    new_node->base_adr = current->base_adr;
    new_node->top_adr = new_node->base_adr + size;
    new_node->free = false;

    struct linkedList *last_node = current;
    while(last_node->next != NULL)
        last_node = last_node->next;
    last_node->next = new_node;
    new_node->next = NULL;
}

void firstFitAllocator(struct linkedList **list, char* id, int size) {
    insertLinkedList(list, id, size);
}