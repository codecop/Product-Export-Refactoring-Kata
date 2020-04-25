#include <stdbool.h>
#include <stdlib.h>

#include "LinkedMap.h"

void linkedMapPut(struct LinkedMap** head, const char* name, const void* data)
{
    struct LinkedMap *newNode, *temp;

    for (temp = *head; temp && temp->next; temp = temp->next)
        ;

    newNode = malloc(sizeof(*newNode));
    newNode->name = name;
    newNode->data = data;
    newNode->next = NULL;

    if (temp) {
        temp->next = newNode;
    }
    else {
        *head = newNode;
    }
}

void* linkedMapRemove(struct LinkedMap** head, const char* name)
{
    return NULL;
}

bool linkedMapContains(const struct LinkedMap*, const char* name)
{
    return false;
}

void* linkedMapGet(const struct LinkedMap* head, const char* name)
{
    return NULL;
}
