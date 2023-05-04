#pragma once
#include "pico/stdlib.h"

// A DebounceButton class handles a button state and debounces it, allowing the
// user to check if the button is pressed or not. It is made specifically to use
// the Raspberry Pi Pico-SDK. It is inspired by Bounce2 library, but it is not a
// port of it.
// https://github.com/thomasfredericks/Bounce2/blob/master/src/Bounce2.cpp

class PicoDebounceButton {
public:
  static const bool PRESSED = false;
  static const bool RELEASED = true;

  // The constructor takes the pin number and the debounce interval in ms.
  // The default interval is 10ms.
  // The default state is PRESSED.
  // The default invert is false.
  PicoDebounceButton(uint8_t pin, uint16_t interval = 10, bool state = PRESSED,
                     bool invert = false)
      : mPin(pin), mInterval(interval), mState(state), mInvert(invert) {
    gpio_init(mPin);
    gpio_set_dir(mPin, GPIO_IN);
    gpio_pull_up(mPin);
  }

  // The update() method should be called in the loop() function. It updates the
  // button state and returns true if the button state has changed.
  bool update() {
    bool currentState = mInvert ? !gpio_get(mPin) : gpio_get(mPin);
    uint32_t now = to_ms_since_boot(get_absolute_time());
    if (currentState != mLastState) {
      mLastStateTime = now;
    }
    if ((now - mLastStateTime) > mInterval) {
      if (currentState != mState) {
        mState = currentState;
        return true;
      }
    }
    mLastState = currentState;
    return false;
  }

  // The getState() method returns the current state of the button.
  bool getState() { return mState; }

  // The getPressed() method returns true if the button is pressed.
  bool getPressed() { return mState == PRESSED; }

  // The getReleased() method returns true if the button is released.
  bool getReleased() { return mState == RELEASED; }

  // The getDuration() method returns the duration of the current button state.
  uint32_t getDuration() {
    uint32_t now = to_ms_since_boot(get_absolute_time());
    return now - mLastStateTime;
  }

  // The interval() method returns the debounce interval.
  uint16_t interval() { return mInterval; }

  // The interval() method sets the debounce interval.
  void interval(uint16_t interval) { mInterval = interval; }

  // The invert() method returns the invert state.
  bool invert() { return mInvert; }

  // The invert() method sets the invert state.
  void invert(bool invert) { mInvert = invert; }

private:
  const uint8_t mPin;
  uint16_t mInterval;
  bool mState;
  uint8_t mMode;
  bool mInvert;
  bool mLastState;
  uint32_t mLastStateTime;
};
