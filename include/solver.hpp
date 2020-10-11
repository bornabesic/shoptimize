#pragma once

#include <vector>

#include "meal.hpp"
#include "store.hpp"

using std::vector;

void solve(
    const Store &store,
    const vector<MealComponent> &components,
    const vector<MealDescriptor> &descriptors,
    const std::function<void(vector<Meal>&)> &callback_fn
);