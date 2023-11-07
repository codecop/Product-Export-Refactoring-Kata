import { Order } from "../src/Order";
import { Price } from "../src/Price";
import { Product } from "../src/Product";
import { Store } from "../src/Store";
import { XMLExporter } from "../src/XMLExporter";

describe("XMLExporter", () => {

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
