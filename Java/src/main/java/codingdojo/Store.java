package codingdojo;

import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * Represents a physical Store where you can go and buy products and attend
 * events.
 */
public class Store implements ModelObject {

	private final Map<String, Product> itemsInStock = new HashMap<String, Product>();
	private final String name;
	private final String id;

	public Store(String name, String id) {
		this.name = name;
		this.id = id;
	}

	public Store(String name, String id, Product[] products) {
		this(name, id);
		addStockedItems(products);
	}

	public void addStockedItems(Product... items) {
		for (Product item : items) {
			this.itemsInStock.put(item.getName(), item);
		}
	}

	public void addStoreEvent(StoreEvent storeEvent) {
		this.itemsInStock.put(storeEvent.getName(), storeEvent);
	}

	public void removeStockedItems(Product... items) {
		for (Product item : items) {
			this.itemsInStock.remove(item.getName());
		}
	}

	public boolean hasItem(Product item) {
		return this.itemsInStock.containsKey(item.getName());
	}

	public Product getItem(String name) {
		return this.itemsInStock.get(name);
	}

	@Override
	public String getId() {
		return this.id;
	}

	@Override
	public String toString() {
		return "Store{" + this.name + '}';
	}

	@Override
	public void saveToDatabase() {
		throw new UnsupportedOperationException("missing from this exercise - shouldn't be called from a unit test");
	}

	public String getName() {
		return this.name;
	}

	public Collection<Product> getStock() {
		return Collections.unmodifiableCollection(this.itemsInStock.values());
	}
}
