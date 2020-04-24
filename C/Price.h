extern struct Price* makePrice(double amount, char* currencyCode);
extern char* PriceToString(struct Price* this);
extern char* PriceGetCurrency(struct Price* this);
extern double PriceGetAmount(struct Price* this);
extern double PriceGetAmountInCurrency(struct Price* this, char* currencyCode);
