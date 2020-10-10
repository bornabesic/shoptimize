#pragma once

#include <vector>

#include "meal.hpp"
#include "store.hpp"

using std::vector;

vector<Meal> solve(
    const Store &store,
    const vector<MealComponent> &components,
    const vector<MealDescriptor> &descriptors
);