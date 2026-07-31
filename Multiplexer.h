#pragma once

#include <Arduino.h>

class Multiplexer {
public:
  Multiplexer(uint8_t sigPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t channelCount, bool useToggles = false)
      : sigPin_(sigPin), channelCount_(channelCount), useToggles_(useToggles) {
    selectPins_[0] = s0;
    selectPins_[1] = s1;
    selectPins_[2] = s2;
    selectPins_[3] = s3;

    values_ = (int*)malloc(sizeof(int) * channelCount_);
  }

  void begin() {
    for (uint8_t i = 0; i < 4; ++i) {
      pinMode(selectPins_[i], OUTPUT);
      digitalWrite(selectPins_[i], LOW);
    }

    if (useToggles_) {
        pinMode(sigPin_, INPUT_PULLUP);
    }

    for (uint8_t i = 0; i < channelCount_; ++i) {
      values_[i] = 0;
    }
  }

  int readChannel(uint8_t channel) const {
    selectChannel(channel);
    if (!useToggles_) {
        return analogRead(sigPin_);
    } else {
        return digitalRead(sigPin_) == 0 ? 0 : 1023;
    }
   
  }

  uint8_t readNext() {
    values_[currentReadIndex_] = readChannel(currentReadIndex_);
    uint8_t readIndex = currentReadIndex_;
    if (++currentReadIndex_ >= channelCount_) {
      currentReadIndex_ = 0;
    }
    return readIndex;
  }

  int getValue(uint8_t channel) const {
    if (channel >= channelCount_) {
      return 0;
    }
    return values_[channel];
  }

private:
  void selectChannel(uint8_t channel) const {
    for (uint8_t i = 0; i < 4; ++i) {
      digitalWrite(selectPins_[i], (channel >> i) & 1);
    }
  }

  uint8_t sigPin_;
  uint8_t selectPins_[4];
  uint8_t channelCount_;

  uint8_t currentReadIndex_ = 0;

  bool useToggles_;

  int* values_;
};
