#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "str_utils.h"

typedef struct t_hashtable_entry
{
    char* key;
    void* value;
    t_hashtable_entry* next;
} t_hashtable_entry;

typedef struct t_hashtable
{
    hash_function hash;
    t_hashtable_entry** entries;
    size_t size;
    size_t entries_count;
} t_hashtable;

t_hashtable* hashtable_new(size_t size, hash_function f)
{
    t_hashtable* hashtable = malloc(sizeof(t_hashtable));

    if (!hashtable) return NULL;
    
    hashtable->entries = calloc(size, sizeof(t_hashtable_entry*));

    if (!hashtable->entries)
    {
        free(hashtable);
        return NULL;
    }
    
    hashtable->size = size;
    hashtable->entries_count = 0;
    hashtable->hash = f;

    return hashtable;
}

void hashtable_free(t_hashtable* hashtable, void (free_value)(void*))
{
    if (hashtable == NULL) return;

    for (size_t i = 0; i < hashtable->size; i++)
    {
        t_hashtable_entry* entry = hashtable->entries[i];
        
        while (entry != NULL)
        {
            if (entry->value != NULL && free_value != NULL) {
                free_value(entry->value);
            }
            t_hashtable_entry* next = entry->next;
            free(entry->key);
            free(entry);

            entry = next;
        }
    }
    
    free(hashtable->entries);
    free(hashtable);
}

t_hashtable_value* hashtable_entry_get(t_hashtable* hashtable, char* key)
{
    if (!hashtable || !key) return NULL;

    int index = hashtable->hash(key) % hashtable->size;
    
    t_hashtable_entry* entry = hashtable->entries[index];

    if (!entry) return NULL;

    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry->value;
        }
        entry = entry->next;
    }

    return NULL;
}

bool hashtable_entry_set(t_hashtable* hashtable, char* key, void* value)
{
    if (!hashtable || !key || value == NULL) return false;

    int index = hashtable->hash(key) % hashtable->size;

    t_hashtable_entry* entry;

    if (hashtable->entries[index] == NULL)
    {
        entry = malloc(sizeof(t_hashtable_entry));
        
        if (!entry) return false;

        entry->key = (char*)str_utils_strdup(key);
        entry->value = value;
        entry->next = NULL;
        hashtable->entries[index] = entry;

        hashtable->entries_count++;
    } else
    {
        entry = hashtable->entries[index];
        t_hashtable_entry* prev = NULL;

        while (entry != NULL) {
            if (strcmp(entry->key, key) == 0) {
                entry->value = value;
                return true;
            }
            prev = entry;
            entry = entry->next;
        }

        entry = malloc(sizeof(t_hashtable_entry));
        if (!entry) return false;

        entry->key = str_utils_strdup(key);
        entry->value = value;
        entry->next = NULL;

        prev->next = entry;

        hashtable->entries_count++;
    }

    return true;
}

size_t hashtable_entries_count(t_hashtable* hashtable)
{
    return hashtable ? hashtable->entries_count : 0;
}

t_hashtable_key** hashtable_keys(t_hashtable* hashtable)
{
    t_hashtable_key** keys = malloc(sizeof(char*) * (hashtable->entries_count+1));
    int index = 0;

    for (size_t i = 0; i < hashtable->size; i++)
    {
        t_hashtable_entry* current = hashtable->entries[i];

        while (current != NULL)
        {
            keys[index] = str_utils_strdup(current->key);
            current = current->next;
            index++;
        }        
    }
    keys[hashtable->entries_count] = NULL;

    return keys;
}

t_hashtable_value** hashtable_values(t_hashtable *hashtable)
{
    if (!hashtable) return NULL;

    size_t count = hashtable->entries_count;
    t_hashtable_value **values = malloc((count + 1) * sizeof(void*));
    if (!values) return NULL;

    size_t index = 0;

    for (size_t i = 0; i < hashtable->size; i++) {
        t_hashtable_entry *current = hashtable->entries[i];

        while (current != NULL) {
            values[index++] = current->value;
            current = current->next;
        }
    }

    values[index] = NULL;
    return values;
}

t_hashtable_entry** hashtable_entries(t_hashtable *hashtable)
{
    if (!hashtable) return NULL;

    size_t count = hashtable->entries_count;
    t_hashtable_entry **entries = malloc((count + 1) * sizeof(t_hashtable_entry*));
    if (!entries) return NULL;

    size_t index = 0;

    for (size_t i = 0; i < hashtable->size; i++) {
        t_hashtable_entry *current = hashtable->entries[i];

        while (current != NULL) {
            entries[index++] = current;
            current = current->next;
        }
    }

    entries[index] = NULL;
    return entries;
}

t_hashtable_key* hashtable_entry_key(t_hashtable_entry* entry)
{
    return entry ? entry->key : NULL;
}

t_hashtable_value* hashtable_entry_value(t_hashtable_entry* entry)
{
    return entry ? entry->value : NULL;
}
