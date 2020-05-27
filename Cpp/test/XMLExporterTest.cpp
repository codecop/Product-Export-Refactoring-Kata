#include "ApprovalTests.hpp"
#include "catch2/catch.hpp"

#include "XMLExporter.h"

#include <vector>
#include <Util.h>
#include <StoreEvent.h>

std::string scrubDate(const std::string &input) {
    static const std::regex regex("createdAt='[^']+'");

    int matchNumber = 1;
    auto result = input;
    std::smatch m;
    if (std::regex_search(result, m, regex)) {
        auto guid_match = m.str();
        auto replacement = "createdAt='date_" + std::to_string(matchNumber) + "'";
        result = ApprovalTests::StringUtils::replaceAll(result, guid_match, replacement);
        matchNumber += 1;
    }
    return result;
}

void verifyXml(std::string xml, ApprovalTests::Options options = ApprovalTests::Options()) {
    xml = ApprovalTests::StringUtils::replaceAll(xml, ">", ">\n");
    ApprovalTests::Approvals::verify(xml, options.fileOptions().withFileExtension(".xml"));
}


TEST_CASE("XMLExporter") {
    Product* CherryBloom = new Product("Cherry Bloom", "LIPSTICK01", 30, new Price(14.99, "USD"));
    Product* RosePetal = new Product("Rose Petal", "LIPSTICK02", 30, new Price(14.99, "USD"));
    Product* BlusherBrush = new Product("Blusher Brush", "TOOL01", 50, new Price(24.99, "USD"));
    Product* EyelashCurler = new Product("Eyelash curler", "TOOL01", 100, new Price(19.99, "USD"));
    Product* WildRose = new Product("Wild Rose", "PURFUME01", 200, new Price(34.99, "USD"));
    Product* CocoaButter = new Product("Cocoa Butter", "SKIN_CREAM01", 250, new Price(10.99, "USD"));

    std::vector<Product *> storeProducts;
    storeProducts.push_back(CherryBloom);
    storeProducts.push_back(RosePetal);
    Store* FlagshipStore = new Store("Nordstan", "4189", storeProducts);

    SECTION("export store") {
        auto xml = XMLExporter().export_store(FlagshipStore);
        verifyXml(xml);
    }

    /* Store events add themselves to the stocked items at their store */
    Product* Masterclass = new StoreEvent("Eyeshadow Masterclass", "EVENT01",
                                 FlagshipStore, new Price(119.99, "USD"));
    Product* Makeover = new StoreEvent("Makeover", "EVENT02",
                              FlagshipStore, new Price(149.99, "USD"));

    std::vector<Product *> orderProducts;
    orderProducts.push_back(Makeover);
    Order* RecentOrder = new Order("1234", from_iso_date("2018-09-01T00:00Z"),
                            FlagshipStore, orderProducts);

    std::vector<Product *> oldOrderProducts;
    orderProducts.push_back(CherryBloom);
    Order* OldOrder = new Order("1235", from_iso_date("2017-09-01T00:00Z"),
                         FlagshipStore, oldOrderProducts);

    auto orders = std::vector<Order *>();
    orders.push_back(RecentOrder);
    orders.push_back(OldOrder);

    SECTION("export full") {
        auto xml = XMLExporter().export_full(orders);
        verifyXml(xml);
    }
    SECTION("export tax details") {
        auto xml = XMLExporter().export_tax_details(orders);
        verifyXml(xml);
    }
    SECTION("export history") {
        auto xml = XMLExporter().export_history(orders);
        auto options = ApprovalTests::Options().withScrubber(scrubDate);
        verifyXml(xml, options);
    }
}


