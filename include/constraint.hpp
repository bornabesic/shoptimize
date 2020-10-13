#pragma once

#include <vector>
#include <string>

#include "meal.hpp"
#include "solver.hpp"

using std::vector;
using std::string;

// ----------------------------------------- Constraints -----------------------------------------
class Constraint {

    public:
        virtual bool check(const Context &context, const vector<Meal> &meals) const = 0;

};

class MaxBudgetConstraint : public Constraint {
    private:
        float max_budget;

    public:
        MaxBudgetConstraint(float max_budget);
        bool check(const Context &context, const vector<Meal> &meals) const override;

};

class ComponentCountConstraint : public Constraint {
    private:
        string component_name;
        long int min, max;

    public:
        ComponentCountConstraint(const string &component_name, long int min = -1, long int max = -1);
        bool check(const Context &context, const vector<Meal> &meals) const override;

};