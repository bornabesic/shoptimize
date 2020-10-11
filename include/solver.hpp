#pragma once

#include <vector>

#include "meal.hpp"
#include "store.hpp"

using std::vector;

// ----------------------------------------- Context -----------------------------------------

class Constraint;

struct Context {
    const Store &store;
    const vector<MealComponent> &components;
    const vector<MealDescriptor> &descriptors;
    const vector<const Constraint *> &constraints;
    const std::function<void(const vector<Meal> &, float)> &callback_fn;
};


// ----------------------------------------- Constraints -----------------------------------------
class Constraint {

    public:
        virtual bool check(const Context &context, const vector<Meal> &meals) const = 0;

};

class MaxBudgetConstraint : public Constraint {
    private:
        float max_budget;

    public:
        MaxBudgetConstraint(float max_budget) : max_budget(max_budget) {}
        bool check(const Context &context, const vector<Meal> &meals) const override;

};

// ----------------------------------------- Solver -----------------------------------------

void solve(
    const Store &store,
    const vector<MealComponent> &components,
    const vector<MealDescriptor> &descriptors,
    const vector<const Constraint *> &constraints,
    const std::function<void(const vector<Meal> &, float)> &callback_fn
);
