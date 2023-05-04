#include "bsp/board.h"
#include "hardware/gpio.h"
#include "include/DebounceButton.hpp"
#include "pico/stdlib.h"

#include "tusb.h"
#include <cstdint>
#include <stdio.h>

// Setup Pin 1 as an input
constexpr auto button_pin = 0;
auto buttonReadState = gpio_get(button_pin);

// Midi buffer
constexpr auto buffer_size = 3;
uint8_t midibuffer[buffer_size];

void sendNoteOn(unsigned int note, unsigned int velocity,
                unsigned int channel) {
  // Create and send a single MIDI note on message
  const auto cable_num = 0;
  const auto eventType = 0x90;

  midibuffer[0] = static_cast<uint8_t>(eventType | channel);
  midibuffer[1] = note;
  midibuffer[2] = velocity;
  tud_midi_stream_write(cable_num, midibuffer, buffer_size);
}

void sendNoteOff(unsigned int note, unsigned int velocity,
                 unsigned int channel) {
  // Create and send a single MIDI note off message
  const auto cable_num = 0;
  const auto eventType = 0x80;

  midibuffer[0] = static_cast<uint8_t>(eventType | channel);
  // midibuffer[1] = static_cast<uint8_t>(eventType | channel);
  midibuffer[1] = note;
  midibuffer[2] = velocity;
  tud_midi_stream_write(cable_num, midibuffer, buffer_size);
}

// This is where the button is being read and the appropriate functions called
void buttonReadTask() {

  // Read the button state
  auto newButtonReadState = gpio_get(button_pin);

  // If the button state has changed
  if (newButtonReadState != buttonReadState) {
    // If the button is pressed
    if (newButtonReadState == 0) {
      // Send a note on message
      sendNoteOn(60, 127, 0);
    } else {
      // Send a note off message
      sendNoteOff(60, 127, 0);
    }

	buttonReadState = newButtonReadState;
  }
}

int main() {
  board_init();
  stdio_init_all();
  tusb_init();

  while (true) {
    buttonReadTask();
    tud_task(); // tinyusb device task
  }

  return 0;
}
