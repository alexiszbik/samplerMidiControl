#pragma once

#include "ToggleController.h"

#include "Const.h"

extern Multiplexer mux3;

// Replace CC numbers with your Bela sampler mapping.
static const ToggleMapping kToggleMappings[] = {
    {&mux3, 0, 50, kMidiChannel},
    {&mux3, 1, 51, kMidiChannel},
    {&mux3, 2, 52, kMidiChannel},
    {&mux3, 3, 53, kMidiChannel},
    {&mux3, 4, 54, kMidiChannel},
    {&mux3, 5, 55, kMidiChannel},
    {&mux3, 6, 56, kMidiChannel},
};

static constexpr size_t kToggleMappingCount =
    sizeof(kToggleMappings) / sizeof(kToggleMappings[0]);
