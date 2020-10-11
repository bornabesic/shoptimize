
#include <iostream>
#include <cstdlib>
#include <chrono>

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
    vector<MealDescriptor> descriptors = parse_description(config);

    std::cout << "Products: " << products.size() << '\n';
    std::cout << "Components: " << components.size() << '\n';
    std::cout << "Stores: " << stores.size() << '\n';

    const Store &store = stores.begin()->second;
    unsigned long int n_solutions = 0;
    auto t_start = std::chrono::high_resolution_clock::now();
    solve(store, components, descriptors, [&](const vector<Meal> &solution, float cost) {
        ++n_solutions;
        for (const auto &meal : solution) {
            std::cout << meal.name() << "\t";
        }
        std::cout << "Cost: " << cost << '\n';
    });
    auto t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> t_delta = t_end - t_start;
    std::cout << "Found " << n_solutions << " solutions in " << t_delta.count() << " seconds." << '\n';

    return 0;
}