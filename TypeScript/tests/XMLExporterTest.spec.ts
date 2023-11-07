import { Order } from "../src/Order";
import { Price } from "../src/Price";
import { Product } from "../src/Product";
import { Store } from "../src/Store";
import { StoreEvent } from "../src/StoreEvent";
import { XMLExporter } from "../src/XMLExporter";
const format = require('xml-formatter');

describe("XMLExporter (CodiumAI)", () => {

  it("Something", () => {

    // TODO: implement this test

    // expect(xml).toMatchSnapshot(); // Use snapshot testing
  });

  // generated with "Test this" tooltip
  it('should generate a valid XML string with the correct version and encoding when given valid input', () => {
    // Arrange
    const orders: Order[] = [
      new Order("1", new Date(), new Store("S1", "Store 1", []),
        [new Product("Product 1", "1", 0.1, new Price(10, "USD"))]),
      new Order("2", new Date(), new Store("S2", "Store 2", []),
        [new Product("Product 2", "2", 1.1, new Price(20, "USD"))]),
    ];

    // Act
    const result = XMLExporter.exportFull(orders);

    // Assert
    expect(result).toMatch(/^<\?xml version="1\.0" encoding="UTF-8"\?>\n<orders>.*<\/orders>$/s);
  });

});

describe('exportFull (Codeium)', () => {

  it('should return correct XML for single order with single product', () => {
    const product = new Product('Product 1', '1', 0, new Price(10, 'USD'));
    const order = new Order('1', new Date(), new Store("S1", "Store 1", []), [product]);

    const result = XMLExporter.exportFull([order]);

    expect(format(result)).toEqual(format(`
<?xml version="1.0" encoding="UTF-8"?>
<orders>
  <order id='1'>
    <product id='1'>
      <price currency='USD'>10</price>
      Product 1
    </product>
  </order>
</orders>`));
  });

  it('should include stylist for event product', () => {
    const store = new Store("S1", "Store 1", []);
    const product = new StoreEvent('Product 1', '1', store, new Price(10, 'USD'));
    const order = new Order('1', new Date(), store, [product]);

    const result = XMLExporter.exportFull([order]);

    expect(format(result)).toContain(`<product id="1" stylist="Celeste Pulchritudo">`);
  });

  it('should include weight for product with weight > 0', () => {
    const product = new Product('Product 1', '1', 5, new Price(10, 'USD'));
    const order = new Order('1', new Date(), new Store("S1", "Store 1", []), [product]);

    const result = XMLExporter.exportFull([order]);

    expect(format(result)).toContain(`<product id="1" weight="5">`);
  });

  it('should return correct XML for multiple orders with multiple products', () => {
    const product1 = new Product('Product 1', '1', 0, new Price(10, 'USD'));
    const product2 = new Product('Product 2', '2', 0, new Price(20, 'USD'));
    const order1 = new Order('1', new Date(), new Store("S1", "Store 1", []), [product1, product2]);

    const product3 = new Product('Product 3', '3', 0, new Price(30, 'USD'));
    const order2 = new Order('2', new Date(), new Store("S1", "Store 1", []), [product3]);

    const result = XMLExporter.exportFull([order1, order2]);

    expect(format(result)).toEqual(format(`
    <?xml version="1.0" encoding="UTF-8"?>
    <orders>
      <order id='1'>
        <product id='1'>
          <price currency='USD'>10</price>
          Product 1
        </product>
        <product id='2'>
          <price currency='USD'>20</price>
          Product 2
        </product>
      </order>
      <order id='2'>
        <product id='3'>
          <price currency='USD'>30</price>
          Product 3
        </product>
      </order>
    </orders>`));
  });

});
