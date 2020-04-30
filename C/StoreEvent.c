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

static const char* store_event_to_string(void* storeEvent);

const struct Product* make_store_event(const char* name,
                                     const char* id,
                                     /*struct Store* location,*/
                                     const struct Price* price)
{
    struct Product* this = make_product(name, id, 0, price);
    this->base.toString = store_event_to_string;
    this->isEvent = true;
    /*
    store_event_set_location(this, location);
    */
    return this;
}

/*
void store_event_set_location(struct StoreEvent* this, struct Store* locationStore)
{
    this->location = locationStore;
    store_add_store_event(locationStore, this);
}
*/

static const char* store_event_to_string(void* storeEvent)
{
    const struct Product* this = (const struct Product*)storeEvent;
    char* s = (char*)malloc(sizeof(char[12 + 20 + 1]));
    sprintf(s, "StoreEvent{%s}", this->name);
    return s;
}
