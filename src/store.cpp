
#include <numeric>
#include <utility>

#include "product.hpp"
#include "store.hpp"

using std::pair;

void Store::register_product(const Product &product, const float price, const Amount amount) {
    this->product_info[product] = {price, amount};
}

bool Store::has_product(const Product &product) {
    return this->product_info.contains(product);
}

const Store::ProductInfo &Store::get_product_info(const Product &product) {
    return this->product_info[product];
}

float Store::get_cost(const Product &product, const Amount &amount) {
    const ProductInfo &info = this->get_product_info(product);
    float unit_price = info.price / info.amount;
    return unit_price * amount;
}

float Store::get_cost(const MealComponent &component) {
    return std::accumulate(
        component.ingredients.begin(),
        component.ingredients.end(),
        0.f,
        [&](const float &sum, const pair<Product, Amount> &p) {
            return sum + this->get_cost(p.first, p.second);
        }
    );
}

float Store::get_cost(const Meal &meal) {
    return std::accumulate(
        meal.components.begin(),
        meal.components.end(),
        0.f,
        [&](const float &sum, const MealComponent &c) {
            return sum + this->get_cost(c);
        }
    );
}

bool Store::sells_all_ingredients(const MealComponent &component) {
    return std::all_of(
        component.ingredients.begin(),
        component.ingredients.end(),
        [&](const pair<Product, Amount> &p) {
            return this->has_product(p.first);
        }
    );
}