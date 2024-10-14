#include "rollcall.h"
#include "linked.h"

Linked_t *Roster = 0;

const int SIZE_ROSTER_AND_ENTRY = (sizeof(roster_entry_t) + sizeof(roster_entry_t *));

void *rc_allocate(int size_bytes, int restricted)
{
    roster_entry_t *roster_entry = malloc(SIZE_ROSTER_AND_ENTRY + size_bytes + 1);
    described_buffer_t *described_buffer = (described_buffer_t *) (((char*)roster_entry) + sizeof(roster_entry_t));

    assert(roster_entry != 0);

    described_buffer->entry_reference = roster_entry;

    roster_entry->owner = 0;
    roster_entry->restricted = restricted;
    roster_entry->size = size_bytes;
    roster_entry->pointer = &(described_buffer->data);

    linked_add(&Roster, roster_entry);
    printf("Allocated Roster[%i] {%i} @%p\n", linked_getSize(Roster), size_bytes, &(described_buffer->data));

    return roster_entry->pointer;
}

void rc_collect()
{
    printf("/------Collecting-----\\\n");
    Linked_t *list = Roster;

    while (list != 0)
    {
        roster_entry_t *roster_entry = list->item;
        assert(roster_entry != 0);

        int **owner_reference = (int **)roster_entry->owner;
        int *owner_points_to = 0;
        if(owner_reference != 0)
        {
            owner_points_to = *owner_reference;
        }
        
        int *owner_should_point_to = (int *)(roster_entry->pointer);

        if (owner_points_to != owner_should_point_to)
        {
            printf("|- Discarding item @%p\n", owner_should_point_to);
            list = linked_remove(&Roster, list);
        }
        else
        {
            list = list->next;
        }
    }

    printf("\\---------------------/\n");
}

void rc_free_all()
{
    Linked_t * list = Roster->next;
    if(Roster == (void*)0)
        return;
        
    free(Roster->item);
    free(Roster);

    while(list != (void*) 0)
    {
        Linked_t * nextPtr = list->next;
        printf("|- Discarding item %p\n", list->item->pointer);
        free(list->item);
        free(list);
        list = nextPtr;
    }
}