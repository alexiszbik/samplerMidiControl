#pragma once

#include "MidiInOut.h"

class MidiPot {
public:
  void begin(uint8_t ccNumber, uint8_t midiChannel) {
    ccNumber_ = ccNumber;
    midiChannel_ = midiChannel;
    lastSentRawValue_ = -1;
    smoothedValue_ = 0;
  }

  void onValueRead(int rawValue) {
    if (lastSentRawValue_ < 0) {
      smoothedValue_ = rawValue;
    } else {
      smoothedValue_ += (rawValue - smoothedValue_) >> kSmoothShift;
    }

    if (lastSentRawValue_ < 0 || abs(smoothedValue_ - lastSentRawValue_) > kDeadband) {
      const int midiValue = map(smoothedValue_, 0, 1023, 0, 127);
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
  static constexpr int kDeadband = 16;
};
