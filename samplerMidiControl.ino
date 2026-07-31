#include "Multiplexer.h"
#include "MidiInOut.h"

#define LED_PIN 13

#define ARCADE_A_PIN 12
#define ARCADE_B_PIN 11

Multiplexer mux(A7, 5, 4, 3, 2, 12);
Multiplexer mux2(A6, A2, A3, A4, A5, 13);
Multiplexer mux3(A1, 9, 8, 7, 6, 7); //toggles

void setup() {
  mux.begin();
  mux2.begin();
  mux3.begin();

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  pinMode(ARCADE_A_PIN, INPUT_PULLUP);
  pinMode(ARCADE_B_PIN, INPUT_PULLUP);

  setupMIDI();
}

void loop() {
  midiLoop();
  mux.readNext();
  mux2.readNext();
  mux3.readNext();
}
