
#include "product.hpp"

bool Product::operator==(const Product &other) const {
    return this->name == other.name &&
           this->type == other.type;
}