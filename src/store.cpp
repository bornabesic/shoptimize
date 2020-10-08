
#include "product.hpp"
#include "store.hpp"

void Store::register_product(const Product &product, const float price, const Amount amount) {
    this->product_info[product] = {price, amount};
}

bool Store::has_product(const Product &product) {
    return this->product_info.contains(product);
}

const Store::ProductInfo &Store::get_product_info(const Product &product) {
    return this->product_info[product];
}