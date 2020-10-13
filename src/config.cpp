
#include "config.hpp"

#include <array>
#include <vector>
#include <cassert>
#include <utility>
#include <algorithm>

#include "yaml-cpp/yaml.h"

#include "product.hpp"
#include "meal.hpp"

using std::array;
using std::vector;
using std::string;
using std::unordered_map;

static constexpr auto days_of_week = {
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};

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
        assert(!products.contains(name));
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

unordered_map<string, Store> parse_stores(const YAML::Node &config, unordered_map<string, Product> &products) {
    unordered_map<string, Store> stores;
    assert(config["stores"]);
    for (const auto &store : config["stores"]) {
        assert(store["name"]);
        assert(store["products"]);
        const string name = store["name"].as<string>();
        assert(!stores.contains(name));
        Store s(name);
        for (const auto &product : store["products"]) {
            const string product_name = product[0].as<string>();
            s.register_product(products[product_name], product[2].as<float>(), product[1].as<Amount>());
        }
        stores[name] = s;
    }
    return stores;
}

static inline vector<MealDescriptor> parse_descriptors_list(const vector<string> &descriptors) {
    vector<MealDescriptor> meal_descriptors;
    for (const auto &meal_string : descriptors) {
        const auto &delimiter_pos = meal_string.find(' ');

        MealComponent::Temperature temperature = parse_component_temperature(
            meal_string.substr(0, delimiter_pos)
        );
        MealComponent::Time time = parse_component_time(
            meal_string.substr(delimiter_pos + 1, meal_string.length() - delimiter_pos)
        );
        meal_descriptors.emplace_back(MealDescriptor(temperature, time));
    }
    return meal_descriptors;
}

vector<MealDescriptor> parse_description(const YAML::Node &config) {
    assert(config["description"]);
    const auto &description = config["description"];
    assert(description["start"]);
    assert(description["days"]);
    assert(description["default"]);

    const auto &start = description["start"].as<string>();
    const auto &day_iterator = std::find(
        days_of_week.begin(),
        days_of_week.end(),
        start
    );
    assert(day_iterator != days_of_week.end());
    const int start_index = day_iterator - days_of_week.begin();

    const int &days = description["days"].as<int>();
    const vector<MealDescriptor> default_ = parse_descriptors_list(
        description["default"].as<vector<string>>()
    );

    vector<MealDescriptor> day_descriptors;
    for (int i = 0; i < days; ++i) {
        const auto index = (start_index + i) % days;
        const auto &day = *(days_of_week.begin() + index);

        const vector<MealDescriptor> &descriptors = (description["override"] && description["override"][day]) ?
        parse_descriptors_list(description["override"][day].as<vector<string>>()) :
        default_;

        day_descriptors.insert(day_descriptors.end(), descriptors.begin(), descriptors.end());
    }

    return day_descriptors;
}

vector<const Constraint *> parse_constraints(const YAML::Node &config) {
    vector<const Constraint *> constraints;
    assert(config["description"]);
    const auto &description = config["description"];
    if (description["max_budget"]) {
        float max_budget = description["max_budget"].as<float>();
        constraints.emplace_back(new MaxBudgetConstraint(max_budget));
    }

    if(description["count"] && description["count"]["components"]) {
        for (const auto &component : description["count"]["components"]) {
            const auto &key = component.first;
            const auto &value = component.second;

            const auto &component_name = key.as<string>();
            long int min = value["min"] ? value["min"].as<long int>() : -1;
            long int max = value["max"] ? value["max"].as<long int>() : -1;
            constraints.emplace_back(new ComponentCountConstraint(component_name, min, max));
        }
    }

    return constraints;
}

Configuration load_configuration(const string &file) {
    YAML::Node config = YAML::LoadFile(file);

    unordered_map<string, Product> products = parse_products(config);
    return {
        products,
        parse_components(config, products),
        parse_stores(config, products),
        parse_description(config),
        parse_constraints(config)
    };
}