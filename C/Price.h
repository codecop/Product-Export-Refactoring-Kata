struct Price;

extern const struct Price* make_price(double, char* currencyCode);
extern const char* price_to_string(const struct Price* this);
extern const char* get_price_currency(const struct Price* this);
extern double get_price_amount(const struct Price* this);
extern double get_price_amount_in_currency(const struct Price* this, char* currencyCode);
