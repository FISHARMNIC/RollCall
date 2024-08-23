#include "rollcall.h"
#include "linked.h"

Linked_t *Roster = 0;

void *rc_allocate(int size_bytes, int restricted)
{
    // Note, here using malloc which also stores size.
    // In compiler use mmap2

    roster_entry_t *roster_entry = malloc(sizeof(roster_entry_t));
    described_buffer_t *described_buffer = malloc(sizeof(roster_entry_t *) + size_bytes);

    assert(roster_entry != 0);
    assert(described_buffer != 0);

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

    int index = 0;
    while (list != 0)
    {
        roster_entry_t *roster_entry = list->item;
        assert(roster_entry != 0);

        int *owner_points_to = *((int **)roster_entry->owner);
        int *owner_should_point_to = (int *)roster_entry->pointer;

        if (owner_points_to != owner_should_point_to)
        {
            printf("|- Discarding Roster[%i] @%p\n", index, owner_should_point_to);
            free(owner_should_point_to - 1);
            list = linked_remove(&Roster, index);
        }
        else
        {

            list = list->next;
            index++;
        }
    }

    printf("\\---------------------/\n");
}