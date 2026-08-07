#pragma once

#include "MidiPot.h"
#include "Multiplexer.h"

struct PotMapping {
  Multiplexer* mux;
  uint8_t muxChannel;
  uint8_t ccNumber;
  uint8_t midiChannel;
};

class PotController {
public:
  void begin(const PotMapping* mappings, size_t count) {
    potCount_ = count < kMaxPots ? count : kMaxPots;

    for (size_t i = 0; i < potCount_; ++i) {
      mappings_[i] = mappings[i];
      pots_[i].begin(mappings[i].ccNumber, mappings[i].midiChannel);
    }
  }

  void onPotRead(Multiplexer* mux, uint8_t channel, int rawValue) {
    for (size_t i = 0; i < potCount_; ++i) {
      if (mappings_[i].mux == mux && mappings_[i].muxChannel == channel) {
        pots_[i].onValueRead(rawValue);
      }
    }
  }

  void resetSentState() {
    for (size_t i = 0; i < potCount_; ++i) {
      pots_[i].resetSentState();
    }
  }

private:
  static constexpr size_t kMaxPots = 32;

  PotMapping mappings_[kMaxPots];
  MidiPot pots_[kMaxPots];
  size_t potCount_ = 0;
};
