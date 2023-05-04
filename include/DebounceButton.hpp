#pragma once
#include "pico/stdlib.h"

class Debounce {
public:
  Debounce(uint8_t pin, uint16_t intervalMS = 200);
  void update();
  auto read();
  auto rose();
  auto fell();

private:
  uint8_t mPin;
  uint16_t mIntervalMS;
  uint32_t mLastTimeMS;
  bool mState;
  bool mLastState;
};

Debounce::Debounce(uint8_t pin, uint16_t interval) {
  gpio_init(mPin);
  gpio_set_dir(mPin, GPIO_IN);
  mState = mLastState = gpio_get(mPin);
  mPin = pin;
  mIntervalMS = interval;
  mLastTimeMS = 0;
}


void Debounce::update() {
  auto nowMS = to_ms_since_boot(get_absolute_time());
  if ((nowMS - mLastTimeMS) >= mIntervalMS) {
    mLastState = mState;
    mState = gpio_get(mPin);
    mLastTimeMS = nowMS;
  }
}

auto Debounce::read() { return mState; }

auto Debounce::rose() { return mState == 1 && mLastState == 0;}

auto Debounce::fell() { return mState == 0 && mLastState == 1;}
