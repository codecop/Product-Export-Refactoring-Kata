#include <stdlib.h>
#include <string.h>

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

bool linkedMapContains(const struct LinkedMap* head, const char* name)
{
    for (const struct LinkedMap* node = head; node; node = node->next) {
        if (strcmp(node->name, name) == 0) {
            return true;
        }
    }
    return false;
}

const void* linkedMapGet(const struct LinkedMap* head, const char* name)
{
    for (const struct LinkedMap* node = head; node; node = node->next) {
        if (strcmp(node->name, name) == 0) {
            return node->data;
        }
    }
    return NULL;
}

const struct LinkedList* linkedMapValues(const struct LinkedMap* head)
{
    struct LinkedList* list = NULL;
    for (const struct LinkedMap* node = head; node; node = node->next) {
        linkedListAppend(&list, node->data);
    }
    return list;
}
