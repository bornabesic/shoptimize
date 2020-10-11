
#include <vector>
#include <functional>
#include <numeric>

#include "solver.hpp"
#include "meal.hpp"
#include "store.hpp"

using std::vector;

static inline float calculate_total_cost(const Context &context, const vector<Meal> &meals) {
    return std::accumulate(
        meals.begin(),
        meals.end(),
        0.f,
        [&](float sum, const Meal &meal) {
            return sum + context.store.get_cost(meal);
        }
    );
}

bool MaxBudgetConstraint::check(const Context &context, const vector<Meal> &meals) const {
    float total_cost = calculate_total_cost(context, meals);
    return total_cost < this->max_budget;

}

static void backtracking(const Context &context, unsigned long int step, vector<Meal> &meals) {
    // Check constraints
    for (const auto &constraint : context.constraints) {
        if (!constraint->check(context, meals)) return;
    }

    // Check if done
    if (step == context.descriptors.size()) {
        float total_cost = calculate_total_cost(context, meals);
        context.callback_fn(meals, total_cost);
        return;
    }

    // Combine meals
    const MealDescriptor &descriptor = context.descriptors[step];
    Meal &meal = meals[step];

    // Main
    for (const auto &main : context.components) {
        if (main.type != MealComponent::Type::MAIN || !descriptor.is_compatible(main)) continue;

        meal.components.emplace_back(main);
        backtracking(context, step + 1, meals); // NOTE

        // Side (optional)
        for (const auto &side : context.components) {
            if (side.type != MealComponent::Type::SIDE || !descriptor.is_compatible(side)) continue;

            meal.components.emplace_back(side);
            backtracking(context, step + 1, meals); // NOTE
            meal.components.pop_back();
        }

        meal.components.pop_back();
    }
    
}

void solve(const Store &store, const vector<MealComponent> &components, const vector<MealDescriptor> &descriptors, const vector<const Constraint *> &constraints, const std::function<void(const vector<Meal> &, float)> &callback_fn) {

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
        {store, available_components, descriptors, constraints, callback_fn},
        0,
        meals
    );
}