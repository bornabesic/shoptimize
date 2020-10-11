
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
    if (argc - 1 != 2) {
        std::cout << "Usage: shoptimize <configfile> <storename>" << '\n';
        std::exit(1);
    }
}

int main(int argc, char **argv) {
    check_args(argc, argv);
    const string &config_file = argv[1];
    const string &store_name = argv[2];

    YAML::Node config = YAML::LoadFile(config_file);

    unordered_map<string, Product> products = parse_products(config);
    vector<MealComponent> components = parse_components(config, products);
    unordered_map<string, Store> stores = parse_stores(config, products);
    vector<MealDescriptor> descriptors = parse_description(config);

    if (!stores.contains(store_name)) {
        std::cout << "Cannot find store '" << store_name << "' in " << config_file << '.' << '\n';
        return 1;
    }

    std::cout << "Products: " << products.size() << '\n';
    std::cout << "Components: " << components.size() << '\n';
    std::cout << "Stores: " << stores.size() << '\n';

    const Store &store = stores[argv[2]];
    unsigned long int n_solutions = 0;
    auto t_start = std::chrono::high_resolution_clock::now();
    vector<Meal> best_solution;
    float best_cost = -1;
    solve(store, components, descriptors, [&](const vector<Meal> &solution, float cost) {
        ++n_solutions;
        if (best_cost == -1 || cost < best_cost) {
            best_solution = solution;
            best_cost = cost;
        }
    });
    auto t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> t_delta = t_end - t_start;

    std::cout << '\n';
    std::cout << "Time: " << t_delta.count() << " s" << '\n';
    if (n_solutions == 0) {
        std::cout << "No solutions found." << '\n';
        return 0;
    }

    std::cout << "Solutions: " << n_solutions << '\n';

    std::cout << '\n';
    std::cout << "Best solution:" << '\n';
    for (const auto &meal : best_solution) {
        std::cout << meal.name() << "\t";
    }
    std::cout << '\n';
    std::cout << "Cost: " << best_cost << '\n';

    return 0;
}