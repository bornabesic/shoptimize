
#include <vector>
#include <functional>
#include <numeric>

#include "solver.hpp"
#include "meal.hpp"
#include "store.hpp"

using std::vector;

struct Context {
    const Store &store;
    const vector<MealComponent> &components;
    const vector<MealDescriptor> &descriptors;
    const std::function<void(const vector<Meal> &, float)> &callback_fn;
};

static void backtracking(const Context &context, unsigned long int step, vector<Meal> &meals) {
    if (step == context.descriptors.size()) {
        float total_cost = std::accumulate(meals.begin(), meals.end(), 0.f, [&](float sum, Meal &meal) {
            Store &store = (Store &) context.store;
            return sum + store.get_cost(meal);
        });
        context.callback_fn(meals, total_cost);
        return;
    }

    const MealDescriptor &descriptor = context.descriptors[step];

    Meal &meal = meals[step];

    // Main
    for (const auto &main : context.components) {
        if (main.type != MealComponent::Type::MAIN || !descriptor.is_compatible(main)) continue;

        meal.components.emplace_back(main);
        backtracking(context, step + 1, meals);

        // Side (optional)
        for (const auto &side : context.components) {
            if (side.type != MealComponent::Type::SIDE || !descriptor.is_compatible(side)) continue;

            meal.components.emplace_back(side);
            backtracking(context, step + 1, meals);
            meal.components.pop_back();
        }

        meal.components.pop_back();
    }
    
}

void solve(const Store &store, const vector<MealComponent> &components, const vector<MealDescriptor> &descriptors, const std::function<void(const vector<Meal> &, float)> &callback_fn) {

    vector<MealComponent> available_components;
    std::copy_if(
        components.begin(),
        components.end(),
        std::back_inserter(available_components),
        [&](const MealComponent &component) {
            return store.sells_all_ingredients(component);
        }
    );

    vector<Meal> meals(descriptors.size());
    backtracking(
        {store, available_components, descriptors, callback_fn},
        0,
        meals
    );
}