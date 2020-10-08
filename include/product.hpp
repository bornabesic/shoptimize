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

        bool operator==(const Product &other) const;
};

namespace std {
    template<>
    struct hash<Product> {
        std::size_t operator()(const Product &product) const noexcept {
            return std::hash<std::string>{}(product.name);
        }
    };
}