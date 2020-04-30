#include <stdlib.h>
#include <string.h>

#include "LinkedMap.h"

struct LinkedMap* make_linked_map()
{
    return NULL;
}

void linked_map_put(struct LinkedMap** head, const char* name, const void* data)
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

bool linked_map_contains(const struct LinkedMap* head, const char* name)
{
    for (const struct LinkedMap* node = head; node; node = node->next) {
        if (strcmp(node->name, name) == 0) {
            return true;
        }
    }
    return false;
}

const void* linked_map_get(const struct LinkedMap* head, const char* name)
{
    for (const struct LinkedMap* node = head; node; node = node->next) {
        if (strcmp(node->name, name) == 0) {
            return node->data;
        }
    }
    return NULL;
}

const struct LinkedList* linked_map_values(const struct LinkedMap* head)
{
    struct LinkedList* list = make_linked_list();
    for (const struct LinkedMap* node = head; node; node = node->next) {
        linked_list_append(&list, node->data);
    }
    return list;
}
