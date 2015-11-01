/*
 * Author: Geoffrey Bonneville <geoffrey.bonneville@gmail.com>
 * TP2
 */

#include "doubly_linked_list.h"

/* init an element */
void INIT_LIST_HEAD(struct list_head *head)
{
        head->next = head;
        head->prev = head;
}

/* add "node" element after "head" */
void list_add(struct list_head *node, struct list_head *head)
{
        if (head->next == NULL) {
                node->next = head;
                node->prev = head;
                head->next = node;
                head->prev = node;
        }
        else {
                node->next = head->next;
                node->prev = head;
                head->next->prev = node;
                head->next = node;
        }
}

/* remove element "node" from a list */
void list_del(struct list_head *node)
{
        node->prev->next = node->next;
        node->next->prev = node->prev;
}
