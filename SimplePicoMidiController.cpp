#include "bsp/board.h"
#include "hardware/gpio.h"
#include "PicoDebounceButton/PicoDebounceButton.hpp"
#include "pico/stdlib.h"

#include "tusb.h"
#include <cstdint>
#include <stdio.h>

// Setup Pin 1 as an input
constexpr auto button_pin = 0;
auto debounceButton =
    picodebounce::PicoDebounceButton(button_pin, 10, picodebounce::PicoDebounceButton::PRESSED, false);

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
  auto newButtonReadState = debounceButton.update();

  // If the button state has changed
  if (newButtonReadState) {
    // If the button is pressed
    if (debounceButton.getPressed()) {
      // Send a note on message
      sendNoteOn(60, 127, 0);
    } else {
      // Send a note off message
      sendNoteOff(60, 127, 0);
    }
  }
}

int main() {
  board_init();
  stdio_init_all();
  tusb_init();

  // Setup button pin
  gpio_init(button_pin);
  gpio_set_dir(button_pin, GPIO_IN);
  gpio_pull_up(button_pin);

  while (true) {
    buttonReadTask();
    tud_task(); // tinyusb device task
  }

  return 0;
}
