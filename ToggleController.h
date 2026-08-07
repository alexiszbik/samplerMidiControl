#pragma once

#include "MidiToggle.h"
#include "Multiplexer.h"

struct ToggleMapping {
  Multiplexer* mux;
  uint8_t muxChannel;
  uint8_t ccNumber;
  uint8_t midiChannel;
};

class ToggleController {
public:
  void begin(const ToggleMapping* mappings, size_t count) {
    toggleCount_ = count < kMaxToggles ? count : kMaxToggles;

    for (size_t i = 0; i < toggleCount_; ++i) {
      mappings_[i] = mappings[i];
      toggles_[i].begin(mappings[i].ccNumber, mappings[i].midiChannel);
    }
  }

  void onToggleRead(Multiplexer* mux, uint8_t channel, int rawValue) {
    for (size_t i = 0; i < toggleCount_; ++i) {
      if (mappings_[i].mux == mux && mappings_[i].muxChannel == channel) {
        toggles_[i].onValueRead(rawValue);
      }
    }
  }

  void resetSentState() {
    for (size_t i = 0; i < toggleCount_; ++i) {
      toggles_[i].resetSentState();
    }
  }

private:
  static constexpr size_t kMaxToggles = 16;

  ToggleMapping mappings_[kMaxToggles];
  MidiToggle toggles_[kMaxToggles];
  size_t toggleCount_ = 0;
};
