#pragma once

#include <vector>
#include <string>

#include "product.hpp"

using std::vector;
using std::string;

class MealComponent {

    enum MealComponentType {
        MAIN_COURSE,
        SIDE_DISH,
        SALAD
    };

    public:
        string name;
        vector<Product> ingredients;
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