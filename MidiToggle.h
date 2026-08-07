#pragma once

#include "MidiInOut.h"

class MidiToggle {
public:
  void begin(uint8_t ccNumber, uint8_t midiChannel) {
    ccNumber_ = ccNumber;
    midiChannel_ = midiChannel;
    lastSentValue_ = -1;
  }

  void onValueRead(int rawValue) {
    const int midiValue = rawValue >= kThreshold ? 127 : 0;

    if (lastSentValue_ < 0 || midiValue != lastSentValue_) {
      sendControlChange(ccNumber_, midiValue, midiChannel_, thisTime);
      lastSentValue_ = midiValue;
    }
  }

  void resetSentState() {
    lastSentValue_ = -1;
  }

private:
  uint8_t ccNumber_ = 0;
  uint8_t midiChannel_ = 1;
  int lastSentValue_ = -1;

  static constexpr int kThreshold = 512;
};
