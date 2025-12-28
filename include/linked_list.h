#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

/**
 * @file linked_list.h
 * @brief Generic doubly linked list implementation in C.
 *
 * Provides a simple and flexible API for managing doubly linked lists
 * with optional cleanup callbacks for stored node data.
 */

/* Forward declarations for linked list types. */
typedef struct t_linked_list      t_linked_list;
typedef struct t_linked_list_node t_linked_list_node;
typedef int (*linked_list_sort_fn)(t_linked_list_node*, t_linked_list_node*);
typedef bool (*linked_list_find_fn)(t_linked_list_node*, void*);
typedef bool (*linked_list_select_fn)(t_linked_list_node*, void*);

/***
 * @brief Creates a new linked list.
 *
 * Allocates and initializes an empty linked list. You may specify
 * an optional callback that is invoked on each node before deletion.
 *
 * @param on_node_delete Callback function called on each node before deletion.
 *                       Pass NULL if no special cleanup is required.
 * @return Pointer to a newly allocated linked list, or NULL on allocation failure.
 */
t_linked_list* linked_list_new(void (*on_node_delete)(t_linked_list_node*));

/**
 * @brief Creates a new linked list from a NULL-terminated array of values.
 *
 * Iterates through the provided array until a NULL pointer is encountered,
 * adding each element as a node in the list.
 *
 * @param list NULL-terminated array of void* values to populate the list.
 * @param on_node_delete Optional callback called on each node before deletion.
 *                       Pass NULL if no cleanup is required.
 * @return Pointer to a newly allocated linked list, or NULL on allocation failure.
 */
t_linked_list* linked_list_new_from_list(void** list, void (*on_node_delete)(t_linked_list_node*));

/**
 * @brief Creates a new linked list from an array of values with a known count.
 *
 * Adds exactly `count` elements from the provided array into the new list.
 *
 * @param array Array of void* values to populate the list.
 * @param count Number of elements in the array.
 * @param on_node_delete Optional callback called on each node before deletion.
 *                       Pass NULL if no cleanup is required.
 * @return Pointer to a newly allocated linked list, or NULL on allocation failure.
 */
t_linked_list* linked_list_new_from_array(void** array, size_t count, void (*on_node_delete)(t_linked_list_node*));

/**
 * @brief Deletes the entire linked list.
 *
 * Frees all nodes and the list structure itself. If a delete callback
 * was provided during creation, it is invoked once per node.
 *
 * @param list Pointer to the linked list. If NULL, nothing happens.
 */
void linked_list_free(t_linked_list *list);

/**
 * @brief Appends a new node to the end of the list.
 *
 * Creates and adds a new node containing the given value.
 *
 * @param list Pointer to the linked list.
 * @param value Pointer to the value to store in the node.
 * @return Pointer to the newly created node, or NULL on failure.
 */
t_linked_list_node* linked_list_add(t_linked_list* list, void* value);

/**
 * @brief Inserts a new node at the specified index.
 *
 * If index equals the list length, the node is appended to the end.
 *
 * @param list Pointer to the linked list.
 * @param index Zero-based position where the node should be inserted.
 * @param value Pointer to the value to store in the node.
 * @return Pointer to the newly created node, or NULL if index is invalid.
 */
t_linked_list_node* linked_list_insert_at(t_linked_list *list, int index, void* value);

/**
 * @brief Removes (but does not free) the node at the given index.
 *
 * The node is detached from the list but not freed.
 * Use linked_list_free_at() to remove and free safely.
 *
 * @param list Pointer to the linked list.
 * @param node Pointer to the node to remove.
 * @return Pointer to the removed node, or NULL if index is invalid.
 */
t_linked_list_node* linked_list_remove(t_linked_list* list, t_linked_list_node* node);

/**
 * @brief Removes (but does not free) the node at the given index.
 *
 * The node is detached from the list but not freed.
 * Use linked_list_free_at() to remove and free safely.
 *
 * @param list Pointer to the linked list.
 * @param index Zero-based index of the node to remove.
 * @return Pointer to the removed node, or NULL if index is invalid.
 */
t_linked_list_node* linked_list_remove_at(t_linked_list* list, int index);

void linked_list_remove_after(t_linked_list* list, int index);

/**
 * @brief Deletes the node at the given index.
 *
 * The node is removed, passed to the delete callback if set,
 * and then freed.
 *
 * @param list Pointer to the linked list.
 * @param index Zero-based index of the node to delete.
 */
void linked_list_free_at(t_linked_list* list, int index);

void linked_list_free_after(t_linked_list* list, int index);

/**
 * @brief Returns the head node of the list.
 *
 * @param list Pointer to the linked list.
 * @return Pointer to the first node, or NULL if the list is empty.
 */
t_linked_list_node* linked_list_head(t_linked_list* list);

/**
 * @brief Returns the tail node of the list.
 *
 * @param list Pointer to the linked list.
 * @return Pointer to the last node, or NULL if the list is empty.
 */
t_linked_list_node* linked_list_tail(t_linked_list* list);

/**
 * @brief Returns the next node after the given one.
 *
 * @param node Pointer to the current node.
 * @return Pointer to the next node, or NULL if at the end.
 */
t_linked_list_node* linked_list_next(t_linked_list_node* node);

/**
 * @brief Returns the previous node before the given one.
 *
 * @param node Pointer to the current node.
 * @return Pointer to the previous node, or NULL if at the beginning.
 */
t_linked_list_node* linked_list_previous(t_linked_list_node* node);

/**
 * @brief Returns the value stored in the given node.
 *
 * @param node Pointer to the node.
 * @return Pointer to the stored value, or NULL if node is NULL.
 */
void* linked_list_value(t_linked_list_node* node);

/**
 * @brief Returns the number of nodes in the list.
 *
 * @param list Pointer to the linked list.
 * @return Number of nodes in the list, or 0 if list is NULL.
 */
size_t linked_list_count(t_linked_list* list);

/**
 * @brief Returns the node at the specified index.
 *
 * @param list Pointer to the linked list.
 * @param index Zero-based index of the node to retrieve.
 * @return Pointer to the node at the index, or NULL if index is invalid.
 */
t_linked_list_node* linked_list_at(t_linked_list* list, int index);

/**
 * @brief Returns a random node from the list.
 *
 * @param list Pointer to the linked list.
 * @return Pointer to a randomly selected node, or NULL if the list is empty.
 */
t_linked_list_node* linked_list_random(t_linked_list* list);

/**
 * @brief Iterates through all nodes in the list.
 *
 * Calls the given callback function once per node, in order.
 * Safe to use even if the callback deletes nodes.
 *
 * @param list Pointer to the linked list.
 * @param func Function to call for each node. If NULL, nothing happens.
 */
void linked_list_for_each(t_linked_list* list, void (*func)(t_linked_list_node*));

/**
 * @brief Sorts the linked list in-place.
 *
 * Uses the provided comparison function to order the nodes.
 *
 * @param list Pointer to the linked list.
 * @param sort_fn Comparison function that returns a negative, zero, or positive value.
 */
void linked_list_sort(t_linked_list* list, linked_list_sort_fn sort_fn);

/**
 * @brief Searches for a node matching a condition.
 *
 * Iterates through all nodes and returns the value of the first node
 * for which the callback returns true.
 *
 * @param list Pointer to the linked list.
 * @param find_fn Callback function that evaluates each node. Should return true for a match.
 * @return Pointer to the value of the first matching node, or NULL if none found.
 */
void* linked_list_find(t_linked_list* list, linked_list_find_fn find_fn, void* context);

/**
 * @brief Searches for a node matching a condition.
 *
 * Iterates through all nodes and returns all the values that satisfies the select function
 * for which the callback returns true.
 *
 * @param list Pointer to the linked list.
 * @param select_fn Callback function that evaluates each node. Should return true for a select.
 * @return Pointer to a newly allocated linked list containing the selected values, or NULL on allocation failure.
 */
t_linked_list* linked_list_select(t_linked_list* list, linked_list_select_fn select_fn, void* context);

void linked_list_concat(t_linked_list* list1, t_linked_list* list2);

#endif /* LINKED_LIST_H */
