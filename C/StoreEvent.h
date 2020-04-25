#include "Price.h"
/*#include "Store.h"*/

struct StoreEvent;

const struct StoreEvent* makeStoreEvent(const char* name,
                                        const char* id,
                                        /*
                                        struct Store* location,
                                        */
                                        const struct Price* price);

extern const char* getStoreEventName(const struct StoreEvent* storeEvent);

/*
extern void storeEventSetLocation(struct StoreEvent* this, struct Store* locationStore);
*/
extern bool storeEventIsEvent(const struct StoreEvent* this);
