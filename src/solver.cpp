
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
    const MealDescriptor &descriptor = context.descriptors[step];
    // TODO
    
}

void solve(const Store &store, const vector<MealComponent> &components, const vector<MealDescriptor> &descriptors) {

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

    auto submit_fn = [&](vector<Meal> &meals) {
        // TODO
    };

    backtracking(
        {store, available_components, descriptors, submit_fn},
        0,
        meals
    );
}