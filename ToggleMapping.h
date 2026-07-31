#pragma once

#include "ToggleController.h"

extern Multiplexer mux3;

// Replace CC numbers with your Bela sampler mapping.
static const ToggleMapping kToggleMappings[] = {
    {&mux3, 0, 26, 1},
    {&mux3, 1, 27, 1},
    {&mux3, 2, 28, 1},
    {&mux3, 3, 29, 1},
    {&mux3, 4, 30, 1},
    {&mux3, 5, 31, 1},
    {&mux3, 6, 32, 1},
};

static constexpr size_t kToggleMappingCount =
    sizeof(kToggleMappings) / sizeof(kToggleMappings[0]);
