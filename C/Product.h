#include <stdbool.h>

#include "Price.h"

struct Product;

extern struct Product* make_product(const char* name, const char* id, long weight, const struct Price* price);
extern void save_product_to_database(const struct Product* this);
extern const char* get_product_name(const struct Product* this);
extern const char* get_product_id(const struct Product* this);
extern const char* product_to_string(const struct Product* this);
extern long get_product_weight(const struct Product* this);
extern const struct Price* get_product_price(const struct Product* this);
extern bool is_product_event(const struct Product* this);

extern void product_set_location(struct Product* this, void* locationStore);
