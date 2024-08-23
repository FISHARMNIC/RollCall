#include "rollcall.h"
#include "linked.h"

#include <assert.h>
#include <stdlib.h>

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

void linked_add(Linked_t **list_db, roster_entry_t *item)
{
    Linked_t* list = *list_db;

    if(list == 0)
    {
        list = malloc(sizeof(Linked_t));
        *list_db = list;
        list->item = item;
        list->next = 0;
    } else {
        list = linked_getLast(list);
        list->next = malloc(sizeof(Linked_t));
        list->next->item = item;
    }
}

Linked_t *linked_remove(Linked_t **list_db, int index)
{
    Linked_t * list = *list_db;
    if (index != 0)
    {
        // rewrite.
        list = linked_readIndex(list, index - 1);
        Linked_t *save_link = list->next->next;
        free(list->next); // issue
        list->next = save_link;
        return list->next;
    }
    else
    {
        Linked_t *save_link = list->next;
        free(list);
        list = save_link;
        *list_db = list;
        return list;
    }
    //return list;
}

int linked_itemExists(Linked_t* list, roster_entry_t* _item)
{
    while (list->next != 0)
    {
        if(list->item == _item)
        {
            return TRUE;
        }
        list = list->next;
    }
    return FALSE;
}