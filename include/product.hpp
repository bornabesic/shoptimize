#pragma once

#include <string>

using std::string;

class Product {

    public:
        enum Type {
            FOOD,
            DRINK
        };

        string name;
        Product::Type type;

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