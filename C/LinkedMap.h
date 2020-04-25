#include <stdbool.h>

#include "LinkedList.h"

struct LinkedMap {
    const char* name;
    const void* data;
    struct LinkedMap* next;
};

extern void linkedMapPut(struct LinkedMap** head, const char* name, const void* data);
extern const void* linkedMapRemove(struct LinkedMap** head, const char* name);
extern bool linkedMapContains(const struct LinkedMap* head, const char* name);
extern const void* linkedMapGet(const struct LinkedMap* head, const char* name);
extern const struct LinkedList* linkedMapValues(const struct LinkedMap* map);
