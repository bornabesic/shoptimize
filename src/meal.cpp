
#include <string>

#include "meal.hpp"

using std::string;

string Meal::name() const {
    string name;
    const size_t index_last = this->components.size() - 1;
    for (size_t i = 0; i < this->components.size(); ++i) {
        name += this->components[i].name;
        if (i < index_last) name += ", ";
    }
    return name;
}

bool MealDescriptor::is_compatible(const MealComponent &component) {
    return component.temperature == this->temperature &&
           component.time == this->time;
}