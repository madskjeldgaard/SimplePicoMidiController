# Big Blinking Button

A simple Raspberry Pi Pico based midi controller that uses the Pico-SDK to make a simple midi controller that reads a button and sends out a midi note when that button is pressed.

It expects the button to be connected to pin 1 (GP0) and pin3 (GND) but you can change this in the code.

## Build

Before building, you need to clone the pico sdk to your computer somewhere, eg:

```bash
git clone https://github.com/raspberrypi/pico-sdk $HOME/pico-sdk
```
Then build the project:

```bash
# Change path to pico sdk if you cloned it somewhere else
export PICO_SDK_PATH=$HOME/pico-sdk; cmake -B build -G Ninja 
cmake --build build
```

