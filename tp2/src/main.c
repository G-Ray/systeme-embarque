/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "doubly_linked_list.h"
#include "hash_table.h"

struct A {
        unsigned int id;
        struct list_head node;
        struct list_head node2;
};

int main(int argc, char *argv[])
{
        struct list_head list;
        struct object *tmp;

        struct A obj;
        struct A obj2;
        struct A obj3;
        struct A *cur;

        struct object o1,
                      o2,
                      o3,
                      o4;

        obj.id = 10;
        obj2.id = 20;
        obj3.id = 30;

        o1.id = 10;
        o2.id = 20;
        o3.id = 30;
        o4.id = 4;

        INIT_LIST_HEAD(&list);

        list_add(& obj.node, &list);
        list_add(& obj2.node, &list);
        list_add(& obj3.node, &list);

        printf("\n************ tests doubly linked list ************\n\n");
        printf("\tthe list should contains 3 objects\n\n");

        list_for_each_entry(cur, &list, node) {
                printf("entry : %d\n", cur->id);
        }

        list_del(&(obj2.node));
        printf("...removing object...%d\n", obj2.id);
        printf("\tit should not print object %d\n\n", obj2.id);

        list_for_each_entry(cur, &list, node) {
                printf("entry : %d\n", cur->id);
        }

        printf("\n************ tests hash table ************\n\n");
        struct hash_table *hashTable = malloc(sizeof(struct hash_table));

        INIT_HASH_TABLE(10, hashTable);

        hash_table_add(hashTable, &o1);
        hash_table_add(hashTable, &o2);
        hash_table_add(hashTable, &o3);
        hash_table_add(hashTable, &o4);

        printf("\t%d should be alone in a cell of the table\n", o4.id);
        hash_table_print_each_entry(hashTable);

        printf("\tit should find object %d\n", o3.id);
        tmp = hash_table_find(hashTable, o3.id);
        if(tmp == NULL)
                printf("not found!\n");
        else
                printf("%d\n", tmp->id);

        printf("\t...removing object %d...\n", o2.id);
        hash_table_remove(hashTable, &o2);
        printf("\tit should not find object %d\n", o2.id);
        tmp = hash_table_find(hashTable, o2.id);
        if(tmp == NULL)
                printf("not found!\n");
        else
                printf("%d\n", tmp->id);

        printf("visual control: \n");
        hash_table_print_each_entry(hashTable);

        free(tmp);
        destroy(hashTable);
        free(hashTable);

        return 0;
}
