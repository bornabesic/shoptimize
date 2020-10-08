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

    enum MealComponentType {
        MAIN_COURSE,
        SIDE_DISH,
        SALAD
    };

    public:
        string name;
        vector<pair<Product, Amount>> ingredients;
        MealComponentType type;

};

class Meal {

    enum MealType {
        COLD,
        HOT
    };

    public:
        string name;
        vector<MealComponent> components;
        MealType type;
};