#ifndef LINKED_LIST
#define LINKED_LIST

#define linked_list_each(declaration, identifier, list, body)                      \
    for (const struct LinkedList* node = list; node; node = node->next) { \
        declaration identifier = (declaration)node->data; \
        body \
    }

struct LinkedList {
    const void* data;
    struct LinkedList* next;
};

#endif

extern struct LinkedList* make_linked_list(void);
extern void linked_list_append(struct LinkedList** head, const void* data);
extern void destroy_linked_list(struct LinkedList* head);
