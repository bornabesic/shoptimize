
#include <iostream>
#include <cstdlib>

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "product.hpp"
#include "meal.hpp"
#include "store.hpp"

void check_args(int argc, char **argv) {
    if (argc - 1 != 1) {
        std::cout << "Usage: shoptimize <configfile>" << '\n';
        std::exit(1);
    }
}

int main(int argc, char **argv) {
    check_args(argc, argv);

    YAML::Node config = YAML::LoadFile(argv[1]);

    unordered_map<string, Product> products = parse_products(config);
    vector<MealComponent> components = parse_components(config, products);
    unordered_map<string, Store> stores = parse_stores(config, products);

    std::cout << "Products: " << products.size() << '\n';
    std::cout << "Components: " << components.size() << '\n';
    std::cout << "Stores: " << stores.size() << '\n';

    return 0;
}