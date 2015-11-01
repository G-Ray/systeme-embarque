/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP2
 */

#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*** MACROS ***/
#define container_of(ptr, type, member) ({ \
        const typeof( ((type *)0)->member ) *__mptr = (ptr); \
        (type *)( (char *)__mptr - offsetof(type, member) );})

/* iterate over a list starting at head */
#define list_for_each_entry(cur, head, member) \
        for (cur = container_of((head)->next, typeof(*cur), member); \
                &cur->member !=(head); \
                cur = container_of(cur->member.next, typeof(*cur), member))
/**************/

struct list_head {
        struct list_head *next;
        struct list_head *prev;
};

/* init an element */
void INIT_LIST_HEAD(struct list_head *head);

/* add "node" element after "head" */
void list_add(struct list_head *node, struct list_head *head);

/* remove element "node" from a list */
void list_del(struct list_head *node);

#endif
