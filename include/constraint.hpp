#pragma once

#include <vector>

#include "meal.hpp"
#include "solver.hpp"

using std::vector;

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