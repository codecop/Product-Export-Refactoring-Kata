import { Order } from "../src/Order";
import { Price } from "../src/Price";
import { Product } from "../src/Product";
import { Store } from "../src/Store";
import { XMLExporter } from "../src/XMLExporter";

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
        const order = new Order('1');
        const product = new Product('1', 'Product 1', new Price('USD', 10), false, 0);
        order.addProduct(product);

        const result = Order.exportFull([order]);

        expect(result).toEqual(`
<?xml version="1.0" encoding="UTF-8"?>
<orders>
  <order id='1'>
    <product id='1'>
      <price currency='USD'>10</price>
      Product 1
    </product>
  </order>
</orders>`);
    });

    it('should include stylist for event product', () => {
        const order = new Order('1');
        const product = new Product('1', 'Product 1', new Price('USD', 10), true, 0);
        order.addProduct(product);

        const result = Order.exportFull([order]);

        expect(result).toContain(`<product id='1' stylist=''>`);
    });

    it('should include weight for product with weight > 0', () => {
        const order = new Order('1');
        const product = new Product('1', 'Product 1', new Price('USD', 10), false, 5);
        order.addProduct(product);

        const result = Order.exportFull([order]);

        expect(result).toContain(`<product id='1' weight='5'>`);
    });

    it('should return correct XML for multiple orders with multiple products', () => {
        const order1 = new Order('1');
        const product1 = new Product('1', 'Product 1', new Price('USD', 10), false, 0);
        const product2 = new Product('2', 'Product 2', new Price('USD', 20), false, 0);
        order1.addProduct(product1);
        order1.addProduct(product2);

        const order2 = new Order('2');
        const product3 = new Product('3', 'Product 3', new Price('USD', 30), false, 0);
        order2.addProduct(product3);

        const result = Order.exportFull([order1, order2]);

        expect(result).toEqual(`
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
    </orders>`);
    });
});
