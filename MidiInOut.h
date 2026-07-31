#pragma once

#include <MIDI.h>
#include <HardwareSerial.h>

#include "BlinkingLed.h"

extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> MIDI;

BlinkingLed ccLed = BlinkingLed(13);

unsigned long thisTime = 0;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setupMIDI() {
  Serial.begin(31250);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOn();
  ccLed.setup();
}

void midiLoop() {
  thisTime = millis();
  ccLed.loop(thisTime);
  while (MIDI.read()) {
    // Incoming MIDI is forwarded to the output via turnThruOn()
  }
}
