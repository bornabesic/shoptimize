
#include <vector>

#include "constraint.hpp"
#include "meal.hpp"

using std::vector;

// ----------------------------------------- Max Budget -----------------------------------------

MaxBudgetConstraint::MaxBudgetConstraint(float max_budget) : max_budget(max_budget) {}

bool MaxBudgetConstraint::check(const Context &context, const vector<Meal> &meals) const {
    float total_cost = context.store.get_cost(meals);
    return total_cost < this->max_budget;
}

// ----------------------------------------- Count -----------------------------------------

ComponentCountConstraint::ComponentCountConstraint(const string &component_name, long int min, long int max) :
component_name(component_name), min(min), max(max) {}

bool ComponentCountConstraint::check(const Context &context, const vector<Meal> &meals) const {
    long int count = 0;
    for (const auto &meal : meals) {
        for (const auto &component : meal.components) {
            if (component.name == this->component_name) ++count;
        }
    }

    bool satisfied = true;
    if (this->min != -1) {
        satisfied = satisfied && (this->min <= count);
    }
    if (this->max != -1) {
        satisfied = satisfied && (count <= this->max);
    }
    return satisfied;
}

//////////////////////////////////

ComponentTypeCountConstraint::ComponentTypeCountConstraint(MealComponent::Type type, long int min, long int max) :
type(type), min(min), max(max) {}

bool ComponentTypeCountConstraint::check(const Context &context, const vector<Meal> &meals) const {
    long int count = 0;
    for (const auto &meal : meals) {
        for (const auto &component : meal.components) {
            if (component.type == this->type) ++count;
        }
    }

    bool satisfied = true;
    if (this->min != -1) {
        satisfied = satisfied && (this->min <= count);
    }
    if (this->max != -1) {
        satisfied = satisfied && (count <= this->max);
    }
    return satisfied;
}