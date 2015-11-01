/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP2
 */

#ifndef HASH_TABLE
#define HASH_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "doubly_linked_list.h"

/* Object structure which can be used for various purposes.
   objects always have an id */
struct object {
        unsigned int id;
        struct list_head node;
        void *data; // Interesting data of your object
};

struct hash_table {
        int size;
        struct list_head **table;
};

/* Initialize a hash table*/
void INIT_HASH_TABLE(int size, struct hash_table *hashTable);

/* Returns a hash calculated from the id */
unsigned int hash(struct hash_table *hashTable, unsigned int id);

/* Add an object to the table */
void hash_table_add(struct hash_table *hashTable, struct object *obj);

/* Remove an object to the table */
void hash_table_remove(struct hash_table *hashTable, struct object *obj);

/* Returns the object if found, else NULL */
struct object* hash_table_find(struct hash_table *hashTable, unsigned int id);

void hash_table_print_each_entry(struct hash_table *hashTable);

/* Destroy a hash table */
void destroy(struct hash_table *hashTable);

#endif
