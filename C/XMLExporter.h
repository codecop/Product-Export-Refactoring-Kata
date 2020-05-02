#include "LinkedList.h"
#include "Store.h"

extern const char* export_full(const struct LinkedList* orders);
extern const char* export_tax_details(struct LinkedList* orders);
extern const char* export_store(struct Store* store);
extern const char* export_history(struct LinkedList* orders);
