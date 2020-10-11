
#include <vector>

#include "constraint.hpp"
#include "meal.hpp"

using std::vector;

// ----------------------------------------- Constraints -----------------------------------------

bool MaxBudgetConstraint::check(const Context &context, const vector<Meal> &meals) const {
    float total_cost = context.store.get_cost(meals);
    return total_cost < this->max_budget;

}