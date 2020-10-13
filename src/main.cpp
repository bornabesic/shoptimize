
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <cmath>

#include "config.hpp"
#include "meal.hpp"
#include "store.hpp"
#include "solver.hpp"

template <unsigned long N>
static float round(float number) {
    static constexpr float factor = std::pow(10.f, N);
    return std::round(number * factor) / factor;
}

static void check_args(int argc, char **argv) {
    if (argc - 1 != 2) {
        std::cout << "Usage: shoptimize <configfile> <storename>" << '\n';
        std::exit(1);
    }
}

int main(int argc, char **argv) {
    check_args(argc, argv);
    const string &config_file = argv[1];
    const string &store_name = argv[2];

    Configuration config = load_configuration(config_file);

    if (!config.stores.contains(store_name)) {
        std::cout << "Cannot find store '" << store_name << "' in " << config_file << '.' << '\n';
        return 1;
    }

    std::cout << "Products: " << config.products.size() << '\n';
    std::cout << "Components: " << config.components.size() << '\n';
    std::cout << "Stores: " << config.stores.size() << '\n';
    std::cout << "Meals: " << config.descriptors.size() << '\n';
    std::cout << "Constraints: " << config.constraints.size() << '\n';

    const Store &store = config.stores.at(argv[2]);
    unsigned long int n_solutions = 0;
    auto t_start = std::chrono::high_resolution_clock::now();
    vector<Meal> best_solution;
    float best_cost = -1;
    solve(config, store, [&](const vector<Meal> &solution, float cost) {
        ++n_solutions;
        if (best_cost == -1 || cost < best_cost) {
            best_solution = solution;
            best_cost = cost;
        }
    });
    auto t_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> t_delta = t_end - t_start;

    std::cout << '\n';
    std::cout << "Time: " << round<3>(t_delta.count()) << " s" << '\n';
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
    std::cout << "Cost: " << round<2>(best_cost) << '\n';

    return 0;
}