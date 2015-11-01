/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP2
 */

#include "hash_table.h"

void INIT_HASH_TABLE(int size, struct hash_table *hashTable) {
        int i;

        hashTable->size = size;
        hashTable->table = malloc(size * sizeof(struct list_head *));

        if (hashTable->table == NULL)
                return NULL; //out of memory

        for(i=0; i<size; i++) {
                hashTable->table[i] = malloc(sizeof(struct list_head));
                if (hashTable->table[i] == NULL) return NULL;
                INIT_LIST_HEAD(hashTable->table[i]);
        }
}

unsigned int hash(struct hash_table *hashTable, unsigned int id) {
        /* TODO: defines a better hash function */
        return id % hashTable->size;
}

void hash_table_add(struct hash_table *hashTable, struct object *obj) {
        unsigned int h = hash(hashTable, obj->id);
        struct list_head *list = hashTable->table[h];
        list_add(& obj->node, list);

        return;
}

void hash_table_remove(struct hash_table *hashTable, struct object *obj) {
        list_del(& obj->node);

        return;
}

void hash_table_print_each_entry(struct hash_table *hashTable) {
        int i;
        struct object *cur = NULL;

        for(i=0; i<hashTable->size; i++) {
                printf("\n %d=> ", i);
                struct list_head *list = hashTable->table[i];

                list_for_each_entry(cur, list, node) {
                        printf("%d, ", cur->id);
                }
        }
}

struct object* hash_table_find(struct hash_table *hashTable, unsigned int id) {
        struct object *cur = NULL;
        unsigned int h = hash(hashTable, id);

        struct list_head *list = hashTable->table[h];

        list_for_each_entry(cur, list, node) {
                if (cur->id == id) return cur;
        }
        printf("\n");

        return NULL; //not found
}

void destroy(struct hash_table *hashTable) {
        int i;

        for(i=0; i<hashTable->size; i++) {
                free(hashTable->table[i]);
        }

        free(hashTable->table);
}
