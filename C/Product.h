#include <stdbool.h>

#include "Price.h"

struct Product;

extern const struct Product* make_product(char* name, char* id, long weight, struct Price* price);
extern const char* get_product_name(const struct Product* this);
extern long get_product_weight(const struct Product* this);
extern const struct Price* get_product_price(const struct Product* this);
extern bool is_product_event(const struct Product* this);
