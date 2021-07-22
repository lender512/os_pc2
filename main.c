#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *size = argv[1];
  struct linkedList *head = initMemory(atoi(size));

  char string[256];
  do {
    printf("allocator> ");
    gets(string);
    char *arguments[64];
    int counter = 0;
    char *token = strtok(string, " ");
    while (token != NULL) {
      arguments[counter] = token;
      counter++;
      token = strtok(NULL, " ");
    }
    if (strcmp(arguments[0], "RQ") == 0) {
      if (strcmp(arguments[3], "W") == 0) {
        allocateW(&head, arguments[1], atoi(arguments[2]));
      } else if (strcmp(arguments[3], "B") == 0) {
        allocateB(&head, arguments[1], atoi(arguments[2]));
      } else if (strcmp(arguments[3], "F") == 0) {
        allocateF(&head, arguments[1], atoi(arguments[2]));
      }
    } else if (strcmp(arguments[0], "RL") == 0) {
      deallocate(head, arguments[1]);
    } else if (strcmp(arguments[0], "C") == 0) {
      compaction(&head);
    } else if (strcmp(arguments[0], "STAT") == 0) {
      printMemory(head);
    } else {
      printf("Please enter valid instruction\n");
    }
  } while (strcmp(string, "X") != 0);

  return 0;
}
