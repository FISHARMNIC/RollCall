#include "rollcall.h"
#include "linked.h"

#include <assert.h>
#include <stdlib.h>

void linked_init(Linked_t **list)
{
    *list = 0;
}

Linked_t *linked_readIndex(Linked_t *list, int index)
{
    while (index > 0)
    {
        assert(list->next != 0);
        list = list->next;
        index--;
    }
    return list;
}

Linked_t *linked_getLast(Linked_t *list)
{
    while (list->next != 0)
    {
        list = list->next;
    }
    return list;
}

int linked_getSize(Linked_t *list)
{
    int index = 0;
    while (list->next != 0)
    {
        list = list->next;
        index++;
    }
    return index;
}

void linked_add(Linked_t *list, roster_entry_t *item)
{
    if ((list->item == 0) && (linked_getSize(list) == 0))
    {
        list->item = item;
    }
    else
    {
        list = linked_getLast(list);
        list->next = malloc(sizeof(Linked_t *));
        list->next->item = item;
    }
}

Linked_t *linked_remove(Linked_t *list, int index)
{
    if (index != 0)
    {
        list = linked_readIndex(list, index - 1);
        Linked_t *save_link = list->next->next;
        free(list->next); // issue
        list->next = save_link;
    } else {
        list->item = 0;
    }
    return list;
}