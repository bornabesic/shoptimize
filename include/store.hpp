#pragma once

#include <string>
#include <unordered_map>

#include "product.hpp"
#include "meal.hpp"

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

        float get_cost(const Product &product, const Amount &amount);
        float get_cost(const MealComponent &component);
        float get_cost(const Meal &meal);

};