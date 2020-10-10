#pragma once

#include <string>
#include <unordered_map>

#include "product.hpp"
#include "meal.hpp"

using std::vector;
using std::string;
using std::unordered_map;

class Store {

    public:
        struct ProductInfo {
            float price;
            Amount amount;
        };

        string name;
        Store() {};
        Store(const string &name) : name(name) {};

        void register_product(const Product &product, const float price, const Amount amount);
        bool has_product(const Product &product) const;
        bool sells_all_ingredients(const MealComponent &component) const;
        const ProductInfo &get_product_info(const Product &product);

        float get_cost(const Product &product, const Amount &amount);
        float get_cost(const MealComponent &component);
        float get_cost(const Meal &meal);

    private:
        unordered_map<Product, Store::ProductInfo> product_info;

};