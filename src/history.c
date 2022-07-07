#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

/* Initialize the linked list to keep the history. */
List* init_history()
{
  List *history = (List*) malloc(sizeof(List));
  return history;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str)
{
  /* Used to determine length of input string.*/
  int len = 0;
  char *ptr = str;
  while (*ptr){
    ptr++;
    len++;
  }
  /* Creating a new node and copying the string into it. */
  Item *new = (Item*) malloc(sizeof(Item));
  new->str = copy_str(str, len);

  /* Creates variables to traverse list and determine position of node.*/ 
  int count = 0;
  Item *iterator = list->root;

  if (iterator){
    while (iterator->next) {
      count++;
      iterator = iterator->next;
    }
    iterator->next = new;
  }
  else {
    list->root = new;
  }
  new->id = count;
}

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id)
{
  /* Uses a temporary iterator to traverse the linked list until
     the id has been reached.*/
  Item *iterator = list->root;
  for (int i = 0; i < id; i++) {
    iterator = iterator->next;
  }
  return iterator->str;
}

/* Print the entire contents of the list.*/
void print_history(List *list)
{
  Item *iterator = list->root;
  while (iterator->next) {
    printf("[%d] - %s\n", iterator->id, iterator->str);
    iterator = iterator->next;
  }
  printf("[%d] - %s\n", iterator->id, iterator->str);
}

/* Free the history list and the string it references. */
void free_history(List *list)
{
  Item *current = list->root;
  Item *next;
  while (current){
    next = current->next;
    free(current->str);
    free(current);
    current = next;
  }
  free(list);
}
