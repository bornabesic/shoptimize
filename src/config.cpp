
#include "config.hpp"

#include <iostream>
#include <vector>
#include <cassert>
#include <utility>

#include "yaml-cpp/yaml.h"

#include "product.hpp"
#include "meal.hpp"

using std::vector;
using std::string;
using std::unordered_map;

static Product::Type parse_product_type(const string &type) {
    if (type == "food")
        return Product::Type::FOOD;
    else if (type == "drink")
        return Product::Type::DRINK;
    else
        assert(false);
}

static MealComponent::Type parse_component_type(const string &type) {
    if (type == "main")
        return MealComponent::Type::MAIN;
    else if (type == "side")
        return MealComponent::Type::SIDE;
    else
        assert(false);
}

static MealComponent::Temperature parse_component_temperature(const string &temperature) {
    if (temperature == "hot")
        return MealComponent::Temperature::HOT;
    else if (temperature == "cold")
        return MealComponent::Temperature::COLD;
    else
        assert(false);
}

static MealComponent::Time parse_component_time(const string &time) {
    if (time == "breakfast")
        return MealComponent::Time::BREAKFAST;
    else if (time == "lunch")
        return MealComponent::Time::LUNCH;
    else if (time == "dinner")
        return MealComponent::Time::DINNER;
    else
        assert(false);
}

unordered_map<string, Product> parse_products(const YAML::Node &config) {
    assert(config["products"]);
    std::unordered_map<std::string, Product> products;
    for (const auto &product : config["products"]) {
        assert(product["name"]);
        assert(product["type"]);

        const string name = product["name"].as<string>();
        products[name] = Product{
            name,
            parse_product_type(product["type"].as<string>())
        };
    }
    return products;
}

vector<MealComponent> parse_components(const YAML::Node &config, unordered_map<string, Product> &products) {
    vector<MealComponent> components;
    assert(config["components"]);
    for (const auto &component : config["components"]) {
        assert(component["name"]);
        assert(component["type"]);
        assert(component["temperature"]);
        assert(component["time"]);
        assert(component["ingredients"]);

        vector<pair<Product, Amount>> ingredients;
        for (const auto &ingredient : component["ingredients"]) {
            const string product_name = ingredient[0].as<string>();
            ingredients.emplace_back(std::pair(
                products[product_name],
                ingredient[1].as<Amount>()
            ));
        }

        components.emplace_back(MealComponent{
            component["name"].as<string>(),
            ingredients,
            parse_component_type(component["type"].as<string>()),
            parse_component_temperature(component["temperature"].as<string>()),
            parse_component_time(component["time"].as<string>())
        });
    }
    return components;

}