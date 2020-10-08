#pragma once

#include <string>
#include <unordered_map>

#include "amount.hpp"
#include "product.hpp"

using std::unordered_map;

class Store {

    struct ProductInfo {
        float price;
        Amount amount;
    };

    private:
        unordered_map<Product, ProductInfo> product_info;

    public:
        void register_product(const Product &product, const float price, const Amount amount);
        bool has_product(const Product &product);
        const ProductInfo &get_product_info(const Product &product);

};