#include <stdlib.h>

#include "LinkedList.h"

void linkedListAppend(struct LinkedList** head, const void* data)
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
