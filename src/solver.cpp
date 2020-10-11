
#include <vector>
#include <functional>
#include <numeric>

#include "config.hpp"
#include "solver.hpp"
#include "meal.hpp"
#include "store.hpp"

using std::vector;

// ----------------------------------------- Solver -----------------------------------------

static void backtracking(const Context &context, unsigned long int step, vector<Meal> &meals) {
    // Check constraints
    for (const auto &constraint : context.config.constraints) {
        if (!constraint->check(context, meals)) return;
    }

    // Check if done
    if (step == context.config.descriptors.size()) {
        float total_cost = context.store.get_cost(meals);
        context.callback_fn(meals, total_cost);
        return;
    }

    // Combine meals
    const MealDescriptor &descriptor = context.config.descriptors[step];
    Meal &meal = meals[step];

    // Main
    for (const auto &main : context.config.components) {
        if (main.type != MealComponent::Type::MAIN || !descriptor.is_compatible(main)) continue;

        meal.components.emplace_back(main);
        backtracking(context, step + 1, meals); // NOTE

        // Side (optional)
        for (const auto &side : context.config.components) {
            if (side.type != MealComponent::Type::SIDE || !descriptor.is_compatible(side)) continue;

            meal.components.emplace_back(side);
            backtracking(context, step + 1, meals); // NOTE
            meal.components.pop_back();
        }

        meal.components.pop_back();
    }
    
}

void solve(const Configuration &config, const Store &store, const std::function<void(const vector<Meal> &, float)> &callback_fn) {

    vector<MealComponent> available_components;
    std::copy_if(
        config.components.begin(),
        config.components.end(),
        std::back_inserter(available_components),
        [&](const MealComponent &component) {
            return store.sells_all_ingredients(component);
        }
    );

    vector<Meal> meals(config.descriptors.size());
    backtracking(
        {config, store, callback_fn},
        0,
        meals
    );
}