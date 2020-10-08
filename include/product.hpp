#pragma once

#include <string>

using std::string;

enum ProductType {
    FOOD,
    DRINK
};

enum UsedFor {
    BREAKFAST,
    LUNCH,
    DINNER
};

class Product {
    public:
        string name;
        ProductType type;
        UsedFor used_for; // TODO Enable multiple values
};