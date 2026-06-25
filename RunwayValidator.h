#pragma once
#include "Plane.h"
#include "Runway.h"

struct RunwayValidator {
    static unsigned int MIN_PASSENGER;
    static unsigned int MIN_CARGO;
    static unsigned int MIN_PRIVATE;

    static void validate(const Plane* plane, const Runway* runway);
};
