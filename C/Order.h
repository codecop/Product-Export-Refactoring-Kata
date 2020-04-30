#include <time.h>

#include "LinkedList.h"
#include "Product.h"
#include "Store.h"

struct Order;

extern struct Order* make_order(char* id, time_t date, struct Store* store, struct LinkedList* products);
extern double order_total_dollars(const struct Order* this);
extern time_t get_order_date(const struct Order* this);
extern const struct LinkedList* get_order_products(const struct Order* this);
extern void add_order_product(struct Order* this, const struct Product* product);
extern void add_order_products(struct Order* this, const struct LinkedList* products);
