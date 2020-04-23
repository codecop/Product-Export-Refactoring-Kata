extern struct Price* makePrice(double amount, char* currencyCode);
extern char* toString(struct Price*);
extern char* getCurrency(struct Price*);
extern double getAmount(struct Price*);
extern double getAmountInCurrency(struct Price*, char* currencyCode);
