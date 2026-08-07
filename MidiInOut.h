#pragma once

#include <MIDI.h>
#include <HardwareSerial.h>

#include "BlinkingLed.h"

BlinkingLed ccLed = BlinkingLed(13);

unsigned long thisTime = 0;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void resetAllControls();

void handleStart() {
  resetAllControls();
}


void setupMIDI() {
  Serial1.begin(31250);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOn();
  ccLed.setup();

  MIDI.setHandleStart(handleStart);
}


void sendControlChange(uint8_t ccNumber, uint8_t midiValue, uint8_t midiChannel,
                       unsigned long time) {
  MIDI.sendControlChange(ccNumber, midiValue, midiChannel);
  ccLed.setOn(time);
}

void midiLoop() {
  thisTime = millis();
  ccLed.loop(thisTime);
  while (MIDI.read()) {
    // Incoming MIDI is forwarded to the output via turnThruOn()
  }
}
