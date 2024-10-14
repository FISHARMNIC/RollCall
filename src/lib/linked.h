#ifndef LINKED_H
#define LINKED_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct Linked_t
{
    roster_entry_t* item;
    struct Linked_t* next;
} Linked_t;

Linked_t* linked_readIndex(Linked_t* list, int index);
Linked_t* linked_getLast(Linked_t* list);
void linked_add(Linked_t** list, roster_entry_t* item);
int linked_getSize(Linked_t* list);
Linked_t *linked_remove(Linked_t **list_db, Linked_t *item);
int linked_itemExists(Linked_t* list, roster_entry_t* _item);

#endif