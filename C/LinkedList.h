#include <stdlib.h>

struct LinkedList {
    void* data;
    struct LinkedList* next;
};

extern void linkedListInsert(struct LinkedList** head, void* data);
