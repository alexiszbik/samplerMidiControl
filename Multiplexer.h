#pragma once

#include <Arduino.h>

class Multiplexer {
public:
  Multiplexer(uint8_t sigPin, uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t channelCount)
    : sigPin_(sigPin), channelCount(channelCount) {
    selectPins_[0] = s0;
    selectPins_[1] = s1;
    selectPins_[2] = s2;
    selectPins_[3] = s3;

    values = (int*)malloc(sizeof(int) * channelCount);
  }

  void begin() {
    for (uint8_t i = 0; i < 4; ++i) {
      pinMode(selectPins_[i], OUTPUT);
      digitalWrite(selectPins_[i], LOW);
    }
  }

  int readChannel(uint8_t channel) const {
    selectChannel(channel);
    return analogRead(sigPin_);
  }

  void readNext() {
    values[currentReadIndex] = readChannel(currentReadIndex);
    currentReadIndex++;
    if (currentReadIndex > channelCount) currentReadIndex = 0;
  }

private:
  void selectChannel(uint8_t channel) const {
    for (uint8_t i = 0; i < 4; ++i) {
      digitalWrite(selectPins_[i], (channel >> i) & 1);
    }
  }

  uint8_t sigPin_;
  uint8_t selectPins_[4];
  uint8_t channelCount;

  uint8_t currentReadIndex = 0;

  int* values;
};
