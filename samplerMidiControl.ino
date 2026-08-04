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
Multiplexer mux3(A1, 9, 8, 7, 6, 7, true);  // toggles

MidiToggle extraToggleA;
MidiToggle extraToggleB;

PotController potController;
ToggleController toggleController;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  mux.begin();
  mux2.begin();
  mux3.begin();

  pinMode(ARCADE_A_PIN, INPUT_PULLUP);
  pinMode(ARCADE_B_PIN, INPUT_PULLUP);

  extraToggleA.begin(40, 4);
  extraToggleB.begin(41, 4);

  setupMIDI();
  potController.begin(kPotMappings, kPotMappingCount);
  toggleController.begin(kToggleMappings, kToggleMappingCount);

  delay(1000);
  digitalWrite(LED_PIN, LOW);
}

byte state = 0;

void loop() {
  midiLoop();

  switch (state) {
    case 2:
      {
        uint8_t channel = mux.readNext();
        potController.onPotRead(&mux, channel, mux.getValue(channel));
      }
    case 4:
      {
        uint8_t channel = mux2.readNext();
        potController.onPotRead(&mux2, channel, mux2.getValue(channel));
      }
    case 6:
      {
        uint8_t channel = mux3.readNext();
        toggleController.onToggleRead(&mux3, channel, mux3.getValue(channel));
      }
    case 8:
      {
        int aValue = digitalRead(ARCADE_A_PIN) == LOW ? 1023 : 0;
        extraToggleA.onValueRead(aValue);
      }
    case 10:
      {
        int bValue = digitalRead(ARCADE_B_PIN) == LOW ? 1023 : 0;
        extraToggleB.onValueRead(bValue);
      }
  }
  state++;
  if (state >= 12) state = 0;
}
