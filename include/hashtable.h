#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct t_hashtable t_hashtable;
typedef struct t_hashtable_entry t_hashtable_entry;
typedef char   t_hashtable_key;
typedef void   t_hashtable_value;

typedef unsigned int (*hash_function)(char*);

/**
 * @file hashtable.h
 * @brief Simple hashtable implementation with separate chaining for collisions.
 */

/**
 * @brief Creates a new hashtable with the given number of buckets and hash function.
 *
 * Allocates memory for a hashtable and initializes all buckets to NULL.
 *
 * @param size Number of buckets in the hashtable.
 * @param f Pointer to a hash function that maps keys to integer hash values.
 * @return Pointer to the newly created hashtable, or NULL if memory allocation fails.
 */
t_hashtable* hashtable_new(size_t size, hash_function f);

/**
 * @brief Frees all memory associated with a hashtable.
 *
 * This function will free each entry in the hashtable and optionally free the values
 * using the provided `free_value` function pointer.
 *
 * @param hashtable Pointer to the hashtable to free.
 * @param free_value Function pointer to free each stored value. Can be NULL if values do not need freeing.
 */
void hashtable_free(t_hashtable* hashtable, void (free_value)(void*));

/**
 * @brief Retrieves a value associated with a given key from the hashtable.
 *
 * @param hashtable Pointer to the hashtable.
 * @param key Key string to look up.
 * @return Pointer to the value if found, NULL otherwise.
 */
t_hashtable_value* hashtable_entry_get(t_hashtable* hashtable, char* key);

/**
 * @brief Inserts a new key-value pair or updates an existing one in the hashtable.
 *
 * If the key already exists, the value is replaced. If the key does not exist, a new entry is added.
 *
 * @param hashtable Pointer to the hashtable.
 * @param key Key string to insert or update.
 * @param value Pointer to the value associated with the key.
 * @return true if a new entry was added or an existing value updated, false on allocation failure.
 */
bool hashtable_entry_set(t_hashtable* hashtable, char* key, void* value);

/**
 * @brief Returns the number of buckets in the hashtable.
 *
 * @param hashtable Pointer to the hashtable.
 * @return The total number of buckets, or 0 if hashtable is NULL.
 */
size_t hashtable_entries_count(t_hashtable* hashtable);

/**
 * @brief Returns a NULL-terminated array of all keys in the hashtable.
 *
 * Each key is strdup'ed; the caller is responsible for freeing the array and each string.
 *
 * @param hashtable Pointer to the hashtable.
 * @return NULL-terminated array of keys, or NULL on failure or if hashtable is NULL.
 */
t_hashtable_key** hashtable_keys(t_hashtable* hashtable);

/**
 * @brief Returns a NULL-terminated array of all values in the hashtable.
 *
 * The values are pointers stored in the hashtable; the caller must not free the values themselves.
 *
 * @param hashtable Pointer to the hashtable.
 * @return NULL-terminated array of values, or NULL if hashtable is NULL.
 */
t_hashtable_value** hashtable_values(t_hashtable* hashtable);

/**
 * @brief Returns a NULL-terminated array of all entries in the hashtable.
 *
 * Each entry is a pointer to a `t_hashtable_entry` struct in the hashtable.
 *
 * @param hashtable Pointer to the hashtable.
 * @return NULL-terminated array of entry pointers, or NULL if hashtable is NULL.
 */
t_hashtable_entry** hashtable_entries(t_hashtable* hashtable);

/**
 * @brief Returns the key stored in a given hashtable entry.
 *
 * @param entry Pointer to a hashtable entry.
 * @return Pointer to the key string, or NULL if entry is NULL.
 */
t_hashtable_key* hashtable_entry_key(t_hashtable_entry* entry);

/**
 * @brief Returns the value stored in a given hashtable entry.
 *
 * @param entry Pointer to a hashtable entry.
 * @return Pointer to the value, or NULL if entry is NULL.
 */
t_hashtable_value* hashtable_entry_value(t_hashtable_entry* entry);

#endif /* HASHTABLE_H */
