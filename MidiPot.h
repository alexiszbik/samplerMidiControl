#pragma once

#include "MidiInOut.h"

static const int maxPot = 1006;

class MidiPot {
public:
  void begin(uint8_t ccNumber, uint8_t midiChannel) {
    ccNumber_ = ccNumber;
    midiChannel_ = midiChannel;
    lastSentRawValue_ = -1;
    smoothedValue_ = 0;
  }

  void onValueRead(int rawValue) {
    if (rawValue == 0) {
      smoothedValue_ = 0;
    } else if (lastSentRawValue_ < 0) {
      smoothedValue_ = rawValue;
    } else {
      smoothedValue_ += (rawValue - smoothedValue_) >> kSmoothShift;
    }

    if (lastSentRawValue_ < 0 || abs(smoothedValue_ - lastSentRawValue_) > kDeadband || (smoothedValue_ == 0 && lastSentRawValue_ != smoothedValue_)) {
      const int midiValue = map(smoothedValue_ > maxPot ? maxPot : smoothedValue_, 0, maxPot, 0, 127);
      sendControlChange(ccNumber_, midiValue, midiChannel_, thisTime);
      lastSentRawValue_ = smoothedValue_;
    }
  }

  void resetSentState() {
    lastSentRawValue_ = -1;
  }

private:
  uint8_t ccNumber_ = 0;
  uint8_t midiChannel_ = 1;
  int lastSentRawValue_ = -1;
  int smoothedValue_ = 0;

  static constexpr int kSmoothShift = 3;
  static constexpr int kDeadband = 10;
};
