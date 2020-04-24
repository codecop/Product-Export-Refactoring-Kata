extern struct Price* makePrice(double amount, char* currencyCode);
extern char* priceToString(struct Price* this);
extern char* getPriceCurrency(struct Price* this);
extern double getPriceAmount(struct Price* this);
extern double getPriceAmountInCurrency(struct Price* this, char* currencyCode);
