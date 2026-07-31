#pragma once

#include <MIDI.h>
#include <HardwareSerial.h>

extern midi::MidiInterface<midi::SerialMIDI<HardwareSerial>> MIDI;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial, MIDI);

void setupMIDI() {
  Serial.begin(31250);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOn();
}

void midiLoop() {
  while (MIDI.read()) {
    // Incoming MIDI is forwarded to the output via turnThruOn()
  }
}
