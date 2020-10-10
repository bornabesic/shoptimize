#pragma once

#include <vector>
#include <string>
#include <utility>

#include "amount.hpp"
#include "product.hpp"

using std::vector;
using std::string;
using std::pair;

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

        std::string name() const;

};