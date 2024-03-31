#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>

typedef struct Node
{
  // size of the data type
  size_t size;
  void *data;
  struct Node *next;
} Node;

typedef struct List
{
  Node *head;
  size_t size;

  // used to have a reference to the last node, but
  // this is not a circular linked list
  Node *tail;
} List;

List *list_new();
void list_destroy(List *list);
void list_node_destroy(Node *node);
void list_prepend(List *list, Node *node);
void list_append(List *list, Node *node);
void list_prepend_value(List *list, void *value, size_t size);
void list_append_value(List *list, void *value, size_t size);
Node *list_pop(List *list);
size_t list_size(List *list);

#endif // LINKEDLIST_H