#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linkedList {
  char *id;
  int base_adr;
  int top_adr;
  bool free;
  struct linkedList *next;
};

void printMemory(struct linkedList *list);

struct linkedList *initMemory(int size);

void deallocate(struct linkedList *list, char *id);

// first Fit

void allocateF(struct linkedList **list, char *id, int size);

void allocateW(struct linkedList **list, char *id, int size);

void allocateB(struct linkedList **list, char *id, int size);

void compaction(struct linkedList **list);

struct linkedList *findPrevLinkedList(struct linkedList *list,
                                      struct linkedList *find);

void swapLinkedList(struct linkedList **list, struct linkedList *node1,
                    struct linkedList *node2);

void printMemory(struct linkedList *list);
