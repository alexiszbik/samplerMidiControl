#include "Multiplexer.h"
#include "MidiInOut.h"
#include "PotController.h"
#include "PotMapping.h"
#include "ToggleController.h"
#include "ToggleMapping.h"

#define LED_PIN 13

#define ARCADE_A_PIN 12
#define ARCADE_B_PIN 11

Multiplexer mux(A7, 5, 4, 3, 2, 12);
Multiplexer mux2(A6, A2, A3, A4, A5, 13);
Multiplexer mux3(A1, 9, 8, 7, 6, 7, true); // toggles

PotController potController;
ToggleController toggleController;

void setup() {
  mux.begin();
  mux2.begin();
  mux3.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(ARCADE_A_PIN, INPUT_PULLUP);
  pinMode(ARCADE_B_PIN, INPUT_PULLUP);

  setupMIDI();
  potController.begin(kPotMappings, kPotMappingCount);
  toggleController.begin(kToggleMappings, kToggleMappingCount);
}

void loop() {
  midiLoop();

  uint8_t channel = mux.readNext();
  potController.onPotRead(&mux, channel, mux.getValue(channel));

  channel = mux2.readNext();
  potController.onPotRead(&mux2, channel, mux2.getValue(channel));

  channel = mux3.readNext();
  toggleController.onToggleRead(&mux3, channel, mux3.getValue(channel));
}
