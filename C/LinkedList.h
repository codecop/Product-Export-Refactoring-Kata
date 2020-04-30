#ifndef LINKED_LIST
#define LINKED_LIST

struct LinkedList {
    const void* data;
    struct LinkedList* next;
};

extern void linked_list_append(struct LinkedList** head, const void* data);

#endif
