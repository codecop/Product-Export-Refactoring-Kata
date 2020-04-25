struct Price;

extern const struct Price* makePrice(double amount, char* currencyCode);
extern const char* priceToString(const struct Price* this);
extern double getPriceAmount(const struct Price* this);
extern const char* getPriceCurrency(const struct Price* this);
extern double getPriceAmountInCurrency(const struct Price* this, char* currencyCode);
