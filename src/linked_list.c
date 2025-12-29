#include <rand_utils.h>
#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

typedef struct t_linked_list_node
{
    void                     *value;
    struct t_linked_list_node  *previous;
    struct t_linked_list_node  *next;
} t_linked_list_node;

static t_linked_list_node linked_list_node_create(void *value)
{
    return (t_linked_list_node) { value, NULL, NULL };
}


typedef struct t_linked_list
{
    t_linked_list_node* head;
    t_linked_list_node* tail;
    int               count;
} t_linked_list;

t_linked_list* linked_list_new()
{
    t_linked_list* list = malloc(sizeof(t_linked_list));

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

t_linked_list* linked_list_new_from_list(void** list)
{
    if (list == NULL) return NULL;

    t_linked_list* linkedlist = linked_list_new();
    if (linkedlist == NULL) return NULL;

    for (size_t i = 0; list[i] != NULL; i++)
    {
        linked_list_add(linkedlist, list[i]);
    }

    return linkedlist;
}

t_linked_list* linked_list_new_from_array(void** array, size_t count)
{
    if (array == NULL) return NULL;

    t_linked_list* linkedlist = linked_list_new();
    if (linkedlist == NULL) return NULL;

    for (size_t i = 0; i < count; i++)
    {
        linked_list_add(linkedlist, array[i]);
    }

    return linkedlist;
}

static void linked_list_node_delete(t_linked_list *list, t_linked_list_node *node, linked_list_on_free on_free)
{
    if (on_free != NULL)
    {
        on_free(node);
    }

    node->next = node->previous = NULL;
    free(node);
}

void linked_list_free(t_linked_list *list, linked_list_on_free on_free)
{
    if (list == NULL) return;

    t_linked_list_node *current = list->head;
    while (current != NULL)
    {
        t_linked_list_node *next = linked_list_next(current);
        linked_list_node_delete(list, current, on_free);
        current = next;
    }

    free(list);
}

t_linked_list_node* linked_list_add(t_linked_list *list, void *value)
{
    if (list == NULL) return NULL;

    t_linked_list_node* node = malloc(sizeof(t_linked_list_node));

    *node = linked_list_node_create(value);

    if (list->head == NULL)
    {
        list->head = list->tail = node;
    }
    else
    { 
        list->tail->next = node;
        node->previous = list->tail;
        list->tail = node;
    }
    list->count++;

    return node;
}

t_linked_list_node* linked_list_insert_at(t_linked_list *list, int index, void* value)
{
    if (list == NULL || index < 0 || index > list->count) return NULL;

    if (index == list->count) return linked_list_add(list, value);

    t_linked_list_node* node = malloc(sizeof(t_linked_list_node));

    *node = linked_list_node_create(value);

    t_linked_list_node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    node->next = current;
    node->previous = current->previous;

    if (current->previous != NULL) {
        current->previous->next = node;
    } else {
        list->head = node;
    }

    current->previous = node;
    list->count++;

    return node;
}

t_linked_list_node* linked_list_remove(t_linked_list* list, t_linked_list_node* node)
{
    if (list == NULL || node == NULL) return NULL;

    if (node->previous != NULL)
        node->previous->next = node->next;
    else
        list->head = node->next;

    if (node->next != NULL)
        node->next->previous = node->previous;
    else
        list->tail = node->previous;

    node->next = node->previous = NULL;
    list->count--;

    return node;
}

t_linked_list_node *linked_list_remove_at(t_linked_list *list, int index)
{
    if (list == NULL || index < 0 || index >= list->count) return NULL;

    t_linked_list_node *current = list->head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    if (current->previous != NULL) current->previous->next = current->next;
    else list->head = current->next;

    if (current->next != NULL) current->next->previous = current->previous;
    else list->tail = current->previous;

    current->next = current->previous = NULL;

    list->count--;

    return current;
}

void linked_list_remove_after(t_linked_list* list, int index)
{
    if (!list || index < 0 || index >= list->count)
        return;

    t_linked_list_node* current = list->head;

    for (int i = 0; i < index; i++)
        current = current->next;

    t_linked_list_node* node = current->next;

    current->next = NULL;
    list->tail = current;

    while (node)
    {
        t_linked_list_node* next = node->next;
        free(node);
        list->count--;
        node = next;
    }
}

void linked_list_free_at(t_linked_list *list, int index, linked_list_on_free on_free)
{
    t_linked_list_node *to_remove = linked_list_remove_at(list, index);
    if (to_remove != NULL)
    {
        linked_list_node_delete(list, to_remove, on_free);
    }
}

void linked_list_free_after(t_linked_list* list, int index, linked_list_on_free on_free)
{
    if (!list || index < 0 || index >= list->count)
        return;

    t_linked_list_node* current = list->head;

    for (int i = 0; i < index; i++)
        current = current->next;

    t_linked_list_node* to_free = current->next;

    current->next = NULL;
    list->tail = current;

    while (to_free)
    {
        t_linked_list_node* next = to_free->next;
        linked_list_node_delete(list, to_free, on_free);
        list->count--;
        to_free = next;
    }
}

t_linked_list_node* linked_list_head(t_linked_list* list)
{
    return list ? list->head : NULL;
}

t_linked_list_node* linked_list_tail(t_linked_list* list)
{
    return list ? list->tail : NULL;
}

t_linked_list_node* linked_list_next(t_linked_list_node* node)
{
    return node ? node->next : NULL;
}

t_linked_list_node* linked_list_previous(t_linked_list_node* node)
{
    return node ? node->previous : NULL;
}

void* linked_list_value(t_linked_list_node* node)
{
    return node ? node->value : NULL;
}

size_t linked_list_count(t_linked_list* list)
{
    return (size_t)(list ? list->count : 0);
}

t_linked_list_node* linked_list_at(t_linked_list* list, int index)
{
    t_linked_list_node* current = list->head;
    
    for (int i = 0; i <= index; i++)
    {
        if (current == NULL) return NULL;
        if (i == index) return current;
        current = current->next;
    }
    return NULL;
}

t_linked_list_node* linked_list_random(t_linked_list* list)
{
    int rand_index = rand_utils_int(0, list->count-1);
    return linked_list_at(list, rand_index);
}

void linked_list_sort(t_linked_list *list, linked_list_sort_fn sort_fn) {
    t_linked_list_node *sorted = NULL;
    t_linked_list_node *current = list->head;

    while (current != NULL) {
        t_linked_list_node *next = current->next;

        t_linked_list_node *insert = sorted;
        t_linked_list_node *insert_prev = NULL;

        while (insert && sort_fn(current, insert) >= 0) {
            insert_prev = insert;
            insert = insert->next;
        }

        current->previous = insert_prev;
        current->next = insert;
        if (insert)
            insert->previous = current;
        if (insert_prev)
            insert_prev->next = current;
        else
            sorted = current;

        current = next;
    }

    list->head = sorted;
    t_linked_list_node *tail = sorted;
    while (tail && tail->next)
        tail = tail->next;
    list->tail = tail;
}

void* linked_list_find(t_linked_list* list, linked_list_find_fn find_fn, void* context)
{
    t_linked_list_node* current = list->head;
    while (current)
    {
        if (find_fn(current, context))
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void linked_list_for_each(t_linked_list *list, void (*func)(t_linked_list_node *))
{
    if (list == NULL  || func == NULL)  return;

    t_linked_list_node *current = list->head;
    while (current != NULL)
    {
        t_linked_list_node *next = current->next;
        func(current);
        current = next;
    }
}

t_linked_list* linked_list_select(t_linked_list* list, linked_list_select_fn select_fn, void* context)
{
    t_linked_list* selection = linked_list_new(NULL);
    
    if (!selection)
    {
        return NULL;
    }

    t_linked_list_node* current = list->head;
    while (current)
    {
        if (select_fn(current, context))
        {
            linked_list_add(selection, current->value);
        }
        current = current->next;
    }
    
    return selection;
}

void linked_list_concat(t_linked_list* list1, t_linked_list* list2)
{
    if (!list1 || !list2) return;
    
    if (linked_list_count(list2) == 0) {
        return;
    }
    
    if (linked_list_count(list1) == 0) {
        list1->head = list2->head;
        list1->tail = list2->tail;
        list1->count = list2->count;
    }
    else {
        list1->tail->next = list2->head;
        list2->head->previous = list1->tail;
        list1->tail = list2->tail;
        list1->count += list2->count;
    }
    
    list2->head = NULL;
    list2->tail = NULL;
    list2->count = 0;
}
