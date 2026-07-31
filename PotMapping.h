#pragma once

#include "PotController.h"

extern Multiplexer mux;
extern Multiplexer mux2;

// Replace CC numbers with your Bela sampler mapping.
static const PotMapping kPotMappings[] = {
    // mux (12 channels)
    {&mux, 0, 1, 1},
    {&mux, 1, 2, 1},
    {&mux, 2, 3, 1},
    {&mux, 3, 4, 1},
    {&mux, 4, 5, 1},
    {&mux, 5, 6, 1},
    {&mux, 6, 7, 1},
    {&mux, 7, 8, 1},
    {&mux, 8, 9, 1},
    {&mux, 9, 10, 1},
    {&mux, 10, 11, 1},
    {&mux, 11, 12, 1},

    // mux2 (13 channels)
    {&mux2, 0, 13, 1},
    {&mux2, 1, 14, 1},
    {&mux2, 2, 15, 1},
    {&mux2, 3, 16, 1},
    {&mux2, 4, 17, 1},
    {&mux2, 5, 18, 1},
    {&mux2, 6, 19, 1},
    {&mux2, 7, 20, 1},
    {&mux2, 8, 21, 1},
    {&mux2, 9, 22, 1},
    {&mux2, 10, 23, 1},
    {&mux2, 11, 24, 1},
    {&mux2, 12, 25, 1},
};

static constexpr size_t kPotMappingCount =
    sizeof(kPotMappings) / sizeof(kPotMappings[0]);
