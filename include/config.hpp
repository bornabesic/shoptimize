#pragma once

#include <vector>
#include <cassert>
#include <utility>

#include "yaml-cpp/yaml.h"

#include "product.hpp"
#include "meal.hpp"
#include "store.hpp"
#include "constraint.hpp"

using std::vector;
using std::string;
using std::unordered_map;

struct Constraint;

struct Configuration {
    const unordered_map<string, Product> products;
    const vector<MealComponent> components;
    const unordered_map<string, Store> stores;
    const vector<MealDescriptor> descriptors;
    const vector<const Constraint *> constraints;
};

Configuration load_configuration(const string &file);