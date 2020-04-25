#include <stdbool.h>
#include <stdlib.h>

#include "Product.c"
/*#include "Store.h"*/
#include "Price.h"
#include "StoreEvent.h"

/**
 * Ticket to In-store event, eg. makeover, eyeshadow masterclass
 * or beauty product launch evening reception
 */
struct StoreEvent {
    /* struct Store* location; */
};

static const char* storeEventToString(void* storeEvent);

const struct Product* makeStoreEvent(const char* name,
                                     const char* id,
                                     /*struct Store* location,*/
                                     const struct Price* price)
{
    struct Product* this = makeProduct(name, id, 0, price);
    this->base.toString = storeEventToString;
    this->isEvent = true;
    /*
    storeEventSetLocation(this, location);
    */
    return this;
}

/*
void storeEventSetLocation(struct StoreEvent* this, struct Store* locationStore)
{
    this->location = locationStore;
    storeAddStoreEvent(locationStore, this);
}
*/

static const char* storeEventToString(void* storeEvent)
{
    const struct Product* this = (const struct Product*)storeEvent;
    char* s = (char*)malloc(sizeof(char[12 + 20 + 1]));
    sprintf(s, "StoreEvent{%s}", this->name);
    return s;
}
