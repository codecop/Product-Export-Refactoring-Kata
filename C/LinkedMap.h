#include <stdbool.h>

struct LinkedMap {
    const char* name;
    const void* data;
    struct LinkedMap* next;
};

extern void linkedMapPut(struct LinkedMap** head, const char* name, const void* data);
extern void* linkedMapRemove(struct LinkedMap** head, const char* name);
extern bool linkedMapContains(const struct LinkedMap*, const char* name);
extern void* linkedMapGet(const struct LinkedMap* head, const char* name);
