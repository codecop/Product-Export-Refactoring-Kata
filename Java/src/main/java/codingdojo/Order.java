package codingdojo;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.Date;

public class Order implements ModelObject {

	private final String id;
	private final Date date;
	private Collection<Product> products = new ArrayList<Product>();
	private Store store;

	public Order(String id, Date date, Store store, Product[] products) {
		this.id = id;
		this.date = date;
		this.store = store;
		for (Product product : products) {
			this.addProduct(product);
		}
	}

	public double totalDollars() {
		double dollars = 0D;
		for (Product product : getProducts()) {
			dollars += product.getPrice().getAmountInCurrency("USD");
		}
		return dollars;
	}

	public void addProduct(Product product) {
		this.products.add(product);
	}

	@Override
	public String toString() {
		return "Order{" + id + '}';
	}

	@Override
	public void saveToDatabase() {
		throw new UnsupportedOperationException("missing from this exercise - shouldn't be called from a unit test");
	}

	@Override
	public String getId() {
		return id;
	}

	public Collection<Product> getProducts() {
		return Collections.unmodifiableCollection(products);
	}

	public Date getDate() {
		return date;
	}

	public void addProducts(Product... products) {
		this.products.addAll(Arrays.asList(products));
	}
}
