#pragma once

#include <vector>

#include "meal.hpp"
#include "store.hpp"

using std::vector;

// TODO Change return type
void solve(
    const Store &store,
    const vector<MealComponent> &components,
    const vector<MealDescriptor> &descriptors
);