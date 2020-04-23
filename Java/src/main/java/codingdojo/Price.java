package codingdojo;

public class Price {

	private final double amount;
	private final String currencyCode;

	public Price(double amount, String currencyCode) {
		this.amount = amount;
		this.currencyCode = currencyCode;
	}

	@Override
	public String toString() {
		return "Price{" + this.amount + '}';
	}

	public String getCurrency() {
		return this.currencyCode;
	}

	public double getAmount() {
		return this.amount;
	}

	public double getAmountInCurrency(String currencyCode) {
		if (this.currencyCode.equals(currencyCode)) {
			return this.amount;
		} else {
			throw new UnsupportedOperationException("shouldn't call this from a unit test, it will do a slow db lookup");
		}
	}
}
