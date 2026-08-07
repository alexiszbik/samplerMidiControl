#pragma once

#include "PotController.h"
#include "Const.h"

extern Multiplexer mux;
extern Multiplexer mux2;

// Replace CC numbers with your Bela sampler mapping.
static const PotMapping kPotMappings[] = {
    // mux (12 channels)
    {&mux, 0, 10, kMidiChannel},
    {&mux, 1, 11, kMidiChannel},
    {&mux, 2, 12, kMidiChannel},
    {&mux, 3, 13, kMidiChannel},
    {&mux, 4, 14, kMidiChannel},
    {&mux, 5, 15, kMidiChannel},
    {&mux, 6, 16, kMidiChannel},
    {&mux, 7, 17, kMidiChannel},
    {&mux, 8, 18, kMidiChannel},
    {&mux, 9, 19, kMidiChannel},
    {&mux, 10, 20, kMidiChannel},
    {&mux, 11, 21, kMidiChannel},

    // mux2 (13 channels)
    {&mux2, 0, 30, kMidiChannel},
    {&mux2, 1, 31, kMidiChannel},
    {&mux2, 2, 32, kMidiChannel},
    {&mux2, 3, 33, kMidiChannel},
    {&mux2, 4, 34, kMidiChannel},
    {&mux2, 5, 35, kMidiChannel},
    {&mux2, 6, 36, kMidiChannel},
    {&mux2, 7, 37, kMidiChannel},
    {&mux2, 8, 38, kMidiChannel},
    {&mux2, 9, 39, kMidiChannel},
    {&mux2, 10, 40, kMidiChannel},
    {&mux2, 11, 41, kMidiChannel},
    {&mux2, 12, 42, kMidiChannel},
};

static constexpr size_t kPotMappingCount =
    sizeof(kPotMappings) / sizeof(kPotMappings[0]);
