# Simple Raspberry Pi Pico Midi Controller

A simple Raspberry Pi Pico based midi controller that uses the Pico-SDK to make a simple midi controller that reads a button and sends out a midi note when that button is pressed.

The project includes a simple Debounce library that will debounce the button presses to remove jitter.

It expects the button to be connected to pin 1 (GP0) and pin3 (GND) but you can change this in the code.

The project also includes a simple SuperCollider script set up to receive midi notes from this controller and play a synth accordingly.

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

