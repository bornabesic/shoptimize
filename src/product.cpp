
#include "product.hpp"

bool Product::operator==(const Product &other) const {
    return this->name == other.name &&
           this->type == other.type &&
           this->used_for == other.used_for;
}