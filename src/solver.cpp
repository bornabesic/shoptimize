
#include <vector>
#include <functional>

#include "solver.hpp"
#include "meal.hpp"
#include "store.hpp"

using std::vector;

struct Context {
    const Store &store;
    const vector<MealComponent> &components;
    const vector<MealDescriptor> &descriptors;
    const std::function<void(vector<Meal>&)> &submit_fn;
};

static void backtracking(const Context &context, int step, vector<Meal> &meals) {
    if (step == context.descriptors.size()) {
        context.submit_fn(meals);
        return;
    }

    const MealDescriptor &descriptor = context.descriptors[step];
    // TODO Consider component types (MealComponent::Type)
    // -> Multiple components per meal
    for (const auto &component : context.components) {
        if (descriptor.is_compatible(component)) {
            meals[step].components.emplace_back(component);
            backtracking(context, step + 1, meals);
            meals[step].components.pop_back();
        }
    }
    
}

vector<Meal> solve(const Store &store, const vector<MealComponent> &components, const vector<MealDescriptor> &descriptors) {

    vector<MealComponent> available_components;
    std::copy_if(
        components.begin(),
        components.end(),
        std::back_inserter(available_components),
        [&](const MealComponent &component) {
            return store.sells_all_ingredients(component);
        }
    );

    vector<Meal> solution;
    auto submit_fn = [&](vector<Meal> &meals) {
        solution = meals; // TODO
    };

    vector<Meal> meals(descriptors.size());
    backtracking(
        {store, available_components, descriptors, submit_fn},
        0,
        meals
    );

    return solution;
}