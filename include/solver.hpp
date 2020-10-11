#pragma once

#include <vector>

#include "config.hpp"
#include "meal.hpp"
#include "store.hpp"

using std::vector;

struct Configuration;

// ----------------------------------------- Context -----------------------------------------

struct Context {
    const Configuration &config;
    const Store &store;
    const std::function<void(const vector<Meal> &, float)> &callback_fn;
};

// ----------------------------------------- Solver -----------------------------------------

void solve(
    const Configuration &config,
    const Store &store,
    const std::function<void(const vector<Meal> &, float)> &callback_fn
);
