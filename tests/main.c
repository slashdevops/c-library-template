#include "../include/linkedlist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_list_new()
{
  List *list = list_new();

  assert(list->size == 0);
  assert(list->head == NULL);
  assert(list->tail == NULL);

  list_destroy(list);
}

void test_list_size_new()
{
  List *list = list_new();

  assert(list_size(list) == 0);

  list_destroy(list);
}

void test_prepend_to_new_list()
{
  List *list = list_new();
  Node *node = malloc(sizeof(Node));

  list_prepend(list, node);

  assert(list_size(list) == 1);

  list_destroy(list);
}

void test_prepend_10()
{
  List *list = list_new();

  for (int i = 0; i < 10; i++)
  {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->size = sizeof(int);

    node->data = malloc(sizeof(Node));
    memcpy(node->data, &i, sizeof(int));

    list_prepend(list, node);
  }

  assert(list_size(list) == 10);

  Node *node = list->head;
  for (int i = 0; i < 10; i++)
  {
    assert(node->size == sizeof(int));

    int *val = (int *)node->data;
    // printf("node value = %d, i= %d\n", *val, (9 - i));
    assert(*val == (9 - i));

    node = node->next;
  }

  list_destroy(list);
}

void test_append_10()
{
  List *list = list_new();

  for (int i = 0; i < 10; i++)
  {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    node->size = sizeof(int);

    node->data = malloc(sizeof(Node));
    memcpy(node->data, &i, sizeof(int));

    list_append(list, node);
  }

  assert(list_size(list) == 10);

  Node *node = list->head;
  for (int i = 0; i < 10; i++)
  {
    assert(node->size == sizeof(int));

    int *val = (int *)node->data;
    // printf("node value = %d, i= %d\n", *val, i);
    assert(*val == i);

    node = node->next;
  }

  list_destroy(list);
}

void test_list_destroy_10()
{
  List *list = list_new();

  for (int i = 0; i < 10; i++)
  {
    Node *node = malloc(sizeof(Node));
    node->next = NULL;
    list_prepend(list, node);
  }

  assert(list_size(list) == 10);

  list_destroy(list);
}

void test_list_prepend_value()
{
  List *list = list_new();

  for (int i = 10; i > 0; i--)
  {
    int *val = malloc(sizeof(int));
    *val = i;
    list_prepend_value(list, val, sizeof(int));
  }

  assert(list_size(list) == 10);

  // check elemets in the list
  Node *temp_node = list->head;
  for (int i = 0; i < 10; i++)
  {
    int *val = (int *)temp_node->data;
    // printf("value = %d, size = %zu (bytes)\n", *val, temp_node->size);
    assert(*val == i + 1);

    assert(sizeof(int) == temp_node->size);
    temp_node = temp_node->next;
  }

  list_destroy(list);
}

void test_list_append_value()
{
  List *list = list_new();

  for (int i = 10; i > 0; i--)
  {
    int *val = malloc(sizeof(int));
    *val = i;
    list_append_value(list, val, sizeof(int));
  }

  assert(list_size(list) == 10);

  // check elements in the list
  Node *temp_node = list->head;
  for (int i = 0; i < 10; i++)
  {
    int *val = (int *)temp_node->data;
    // printf("value = %d, size = %zu (bytes)\n", *val, temp_node->size);
    assert(*val == 10 - i);

    assert(sizeof(int) == temp_node->size);
    temp_node = temp_node->next;
  }

  list_destroy(list);
}

void test_list_pop_all()
{
  List *list = list_new();

  for (int i = 0; i < 10; i++)
  {
    Node *node = malloc(sizeof(Node));
    node->data = malloc(sizeof(int));
    memcpy(node->data, &i, sizeof(int));
    node->next = NULL;
    node->size = sizeof(int);

    list_prepend(list, node);
  }

  assert(list_size(list) == 10);

  for (int i = 0; i < 10; i++)
  {
    Node *pop_node = list_pop(list);
    assert(pop_node != NULL);
    // int *val = (int *)pop_node->data;
    // printf("value: %d,  size: %zu\n", *val, pop_node->size);

    list_node_destroy(pop_node);
  }

  list_destroy(list);
}

void tests_run_all(void)
{
  test_list_new();
  test_list_size_new();
  test_prepend_to_new_list();
  test_prepend_10();
  test_append_10();
  test_list_destroy_10();
  test_list_prepend_value();
  test_list_append_value();
  test_list_pop_all();
}

int main(void)
{
  tests_run_all();
}