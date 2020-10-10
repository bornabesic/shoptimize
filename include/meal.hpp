#pragma once

#include <vector>
#include <string>
#include <utility>

#include "product.hpp"

using std::vector;
using std::string;
using std::pair;

typedef float Amount;

class MealComponent {

    public:
        enum Type {
            MAIN,
            SIDE
            // TODO Add others
        };

        enum Temperature {
            COLD,
            HOT
        };

        enum Time {
            BREAKFAST,
            LUNCH,
            DINNER
        };

        string name;
        vector<pair<Product, Amount>> ingredients;
        MealComponent::Type type;
        MealComponent::Temperature temperature;
        MealComponent::Time time;

};

class Meal {

    public:
        vector<MealComponent> components;

        string name() const;

};

class MealDescriptor {

    private:
        MealComponent::Temperature temperature;
        MealComponent::Time time;

    public:
        MealDescriptor(MealComponent::Temperature temperature, MealComponent::Time time) :
        temperature(temperature), time(time) {}

        bool is_compatible(const MealComponent &component);
};