#pragma once

enum Unit {
    KILOGRAMS,
    LITERS
};

struct Amount {
    float value;
    Unit unit;
};