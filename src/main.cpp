
#include <iostream>
#include <cstdlib>

#include "yaml-cpp/yaml.h"

#include "config.hpp"
#include "product.hpp"
#include "meal.hpp"
#include "store.hpp"
#include "solver.hpp"

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

    // TODO Move to config file
    vector<MealDescriptor> descriptors{
        {MealComponent::Temperature::HOT, MealComponent::Time::LUNCH},
        {MealComponent::Temperature::HOT, MealComponent::Time::LUNCH},
        // NOTE {MealComponent::Temperature::HOT, MealComponent::Time::BREAKFAST}
    };

    const Store &store = stores.begin()->second;
    solve(store, components, descriptors, [&](vector<Meal> &solution) {
        for (const auto &meal : solution) {
            std::cout << meal.name() << "\t";
        }
        std::cout << '\n';
    });

    return 0;
}