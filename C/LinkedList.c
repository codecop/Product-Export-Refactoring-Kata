#include <stdlib.h>

#include "LinkedList.h"

struct LinkedList* make_linked_list(void)
{
    return NULL;
}

void linked_list_append(struct LinkedList** head, const void* data)
{
    struct LinkedList *newNode, *temp;

    for (temp = *head; temp && temp->next; temp = temp->next)
        ;

    newNode = malloc(sizeof(*newNode));
    newNode->data = data;
    newNode->next = NULL;

    if (temp) {
        temp->next = newNode;
    }
    else {
        *head = newNode;
    }
}

void destroy_linked_list(struct LinkedList* head)
{
    struct LinkedList* current = head;
    while (current) {
        struct LinkedList* toFree = current;
        current = current->next;
        free(toFree);
    }
}
