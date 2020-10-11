#pragma once

#include <vector>
#include <cassert>
#include <utility>

#include "yaml-cpp/yaml.h"

#include "product.hpp"
#include "meal.hpp"
#include "store.hpp"
#include "solver.hpp"

using std::vector;
using std::string;
using std::unordered_map;

unordered_map<string, Product> parse_products(const YAML::Node &config);
vector<MealComponent> parse_components(const YAML::Node &config, unordered_map<string, Product> &products);
unordered_map<string, Store> parse_stores(const YAML::Node &config, unordered_map<string, Product> &products);
vector<MealDescriptor> parse_description(const YAML::Node &config);
vector<const Constraint *> parse_constraints(const YAML::Node &config);