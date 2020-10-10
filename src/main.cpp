
#include <iostream>

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "product.hpp"
#include "meal.hpp"
#include "store.hpp"


int main(void) {
    YAML::Node config = YAML::LoadFile("config.yaml");

    unordered_map<string, Product> products = parse_products(config);
    vector<MealComponent> components = parse_components(config, products);
    unordered_map<string, Store> stores = parse_stores(config, products);

    std::cout << "Products: " << products.size() << '\n';
    std::cout << "Components: " << components.size() << '\n';
    std::cout << "Stores: " << stores.size() << '\n';

    return 0;
}