#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../hashtable.h"

// Dummy free function just for testing
void dummy_free(void* value) {
    free(value);
}

unsigned int simple_hash(char* key) {
    char* str = (char*)key;
    int hash = 0;
    while (*str) {
        hash = hash * 31 + *str++;
    }
    return hash;
}

int main(void) {
    t_hashtable* ht = hashtable_new(10, simple_hash);
    assert(ht != NULL);

    // Insert some entries
    char* key1 = "foo";
    char* key2 = "bar";

    int* val1 = malloc(sizeof(int));
    int* val2 = malloc(sizeof(int));
    *val1 = 42;
    *val2 = 99;

    assert(hashtable_entry_set(ht, key1, val1) == true);
    assert(hashtable_entry_set(ht, key2, val2) == true);

    assert(hashtable_entries_count(ht) == 2);
    
    // Check get
    int* get_val1 = (int*)hashtable_entry_get(ht, key1);
    int* get_val2 = (int*)hashtable_entry_get(ht, key2);
    assert(get_val1 != NULL && *get_val1 == 42);
    assert(get_val2 != NULL && *get_val2 == 99);

    // Update value
    int* val1_new = malloc(sizeof(int));
    *val1_new = 123;
    assert(hashtable_entry_set(ht, key1, val1_new) == true);
    int* get_val1_new = (int*)hashtable_entry_get(ht, key1);
    assert(get_val1_new != NULL && *get_val1_new == 123);

    // Try get non-existent key
    assert(hashtable_entry_get(ht, "nonexistent") == NULL);

    // Check keys
    char** keys = hashtable_keys(ht);
    assert(strcmp(keys[0], key1) == 0);
    assert(strcmp(keys[1], key2) == 0);
    assert(keys[2] == NULL);

    // Check values
    int** values = (int**)hashtable_values(ht);
    assert(values[0] != NULL && *values[0] == *val1_new);
    assert(values[1] != NULL && *values[1] == *val2);
    assert(values[2] == NULL);

    // Check entries
    t_hashtable_entry** entries = hashtable_entries(ht);
    assert(strcmp(hashtable_entry_key(entries[0]), key1) == 0);
    assert(entries[0] != NULL && *((int*)hashtable_entry_value(entries[0])) == *val1_new);

    assert(strcmp(hashtable_entry_key(entries[1]), key2) == 0);
    assert(entries[1] != NULL && *((int*)hashtable_entry_value(entries[1])) == *val2);

    assert(entries[2] == NULL);

    // Clean up
    hashtable_free(ht, dummy_free);

    free(keys[0]);
    free(keys[1]);
    free(keys);

    printf("All tests passed!\n");
    return 0;
}
